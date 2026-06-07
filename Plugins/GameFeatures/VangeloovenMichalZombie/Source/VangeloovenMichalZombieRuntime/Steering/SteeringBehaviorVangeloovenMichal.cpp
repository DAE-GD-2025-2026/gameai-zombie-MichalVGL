#include "SteeringBehaviorVangeloovenMichal.h"

#include "NavigationSystem.h"
#include "Survivor/SurvivorPawn.h"

// MoveTo

SteeringOutputVangeloovenMichal MoveToVangeloovenMichal::CalculateSteering(float DeltaT, ASurvivorPawn& Pawn)
{
	SteeringOutputVangeloovenMichal Steering{};

	const FVector PawnLocation = Pawn.GetActorLocation();
	const FVector TargetLocation = FVector{ Target.Position, PawnLocation.Z };

	//this should cache the path but due to blending of steeringbehaviors,
	// the path could be invalidated by fleeing from an enemy
	
	UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(Pawn.GetWorld());
	if (!NavSys) return Steering;

	UNavigationPath* Path = NavSys->FindPathToLocationSynchronously(
		Pawn.GetWorld(), PawnLocation, TargetLocation, &Pawn
	);

	if (!Path || !Path->IsValid() || Path->PathPoints.Num() < 2)
		return Steering;

	const FVector ToGoal = TargetLocation - PawnLocation;
	if (FVector2D{ ToGoal }.SquaredLength() < AcceptanceRadiusSq) // arrived
		return Steering; 

	const FVector ToWaypoint = Path->PathPoints[1] - PawnLocation;
	Steering.LinearVelocity = FVector2D{ ToWaypoint }.GetSafeNormal();
	return Steering;
}

// Flee

SteeringOutputVangeloovenMichal FleeVangeloovenMichal::CalculateSteering(float DeltaT, ASurvivorPawn& Pawn)
{
	SteeringOutputVangeloovenMichal Steering{};

	FVector2D Away = FVector2D{Pawn.GetActorLocation()} - Target.Position;
	Steering.LinearVelocity = Away.GetSafeNormal();

	return Steering;
}

//Face

SteeringOutputVangeloovenMichal FaceVangeloovenMichal::CalculateSteering(float DeltaT, ASurvivorPawn& Pawn)
{
	SteeringOutputVangeloovenMichal Steering{};
	 
	FVector2D ToTarget = Target.Position - FVector2D{Pawn.GetActorLocation()};
	const float TargetAngle = FMath::RadiansToDegrees(FMath::Atan2(ToTarget.Y, ToTarget.X));
	const float Angle = FMath::FindDeltaAngleDegrees(Pawn.GetActorRotation().Yaw, TargetAngle);
	Steering.AngularVelocity = Angle;
	
	return Steering;
}

// Blended Steering

BlendedSteeringVangeloovenMichal::BlendedSteeringVangeloovenMichal(const std::vector<WeightedBehavior>& WeightedBehaviors)
	: WeightedBehaviors(WeightedBehaviors)
{
}

SteeringOutputVangeloovenMichal BlendedSteeringVangeloovenMichal::CalculateSteering(float DeltaT, ASurvivorPawn& Pawn)
{
	SteeringOutputVangeloovenMichal Output{};
	SteeringOutputVangeloovenMichal SingleSteering{};
	for (WeightedBehavior& Behaviour : WeightedBehaviors)
	{
		SingleSteering = Behaviour.pBehavior->CalculateSteering(DeltaT, Pawn);

		if (!SingleSteering.LinearVelocity.IsNearlyZero())
			SingleSteering.LinearVelocity.Normalize();

		SingleSteering *= Behaviour.Weight;
		Output = Output + SingleSteering;
	}

	Output.LinearVelocity.Normalize();
	return Output;
}

float BlendedSteeringVangeloovenMichal::GetWeight(const SteeringBehaviorVangeloovenMichal* pBehavior)
{
	auto it = std::ranges::find_if(WeightedBehaviors
		                     , [pBehavior](const WeightedBehavior& Elem)
		                     {
			                     return Elem.pBehavior == pBehavior;
		                     });

	if (it != WeightedBehaviors.end())
		return it->Weight;

	return -1.f;
}

bool BlendedSteeringVangeloovenMichal::SetWeight(SteeringBehaviorVangeloovenMichal* pBehavior, float NewWeight)
{
	auto it = std::ranges::find(WeightedBehaviors, pBehavior, &WeightedBehavior::pBehavior);
	
	if (it != WeightedBehaviors.end())
	{
		it->Weight = NewWeight;
		return true;
	}
	
	return false;
}
