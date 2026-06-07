// Fill out your copyright notice in the Description page of Project Settings.


#include "FaceClosestEnemyVangeloovenMichal.h"

#include "VangeloovenMichalZombieRuntime/Survivor/SurvivorBlackboardVangeloovenMichal.h"

UFaceClosestEnemyVangeloovenMichal::UFaceClosestEnemyVangeloovenMichal()
{
	NodeName = "FaceClosestEnemy";
}

EBTNodeResult::Type UFaceClosestEnemyVangeloovenMichal::ExecuteTask(UBehaviorTreeComponent& OwnerComp,
                                                                    uint8* NodeMemory)
{
	SurvivorBlackboardVangeloovenMichal BB{OwnerComp.GetBlackboardComponent()};

	UZombiesVangeloovenMichal* Zombies = BB.GetThreateningZombies();
	if (Zombies == nullptr)
		return EBTNodeResult::Failed;

	AActor* Self = BB.GetActor();
	
	// Calculate the weights based on the closest zombie

	auto ClosestZombie = std::ranges::min_element(Zombies->Zombies, std::ranges::less{}, [&](const ABaseZombie* Zombie)
	{
		return FVector::DistSquared(Zombie->GetActorLocation(), Self->GetActorLocation());
	});

	if (ClosestZombie == std::ranges::end(Zombies->Zombies))
	{
		return EBTNodeResult::Failed;
	}

	float Distance = FVector::Dist((*ClosestZombie)->GetActorLocation(), Self->GetActorLocation());
	float FleeWeight = MinFleeInfluence;
	
	if (FarFleeDistance > CloseFleeDistance)
	{
		FleeWeight = FMath::Lerp(MaxFleeInfluence, MinFleeInfluence
		                     , (Distance - CloseFleeDistance) / (FarFleeDistance -
			                     CloseFleeDistance));
		FleeWeight = FMath::Clamp(FleeWeight, MinFleeInfluence, MaxFleeInfluence);
	}
	
	float MoveToWeight = 1 - FleeWeight;
	
	// Assign the weights to the blend of the movement
	
	auto* Steering = BB.GetSteeringBehavior();
	if (!Steering)
		return EBTNodeResult::Failed;
	
	auto* Flee = Steering->GetFlee();
	auto* MoveTo = Steering->GetMoveTo();
	
	auto* MainMoveBlend = Steering->GetMoveBehavior();
	auto* MainLookBehavior = Steering->GetLookBehavior();
	
	if (!MoveTo || !Flee
		|| !MainMoveBlend
		|| !MainLookBehavior)
		return EBTNodeResult::Failed;
	
	MainMoveBlend->SetWeight(Flee, FleeWeight);
	MainMoveBlend->SetWeight(MoveTo, 1.f);
	
	
	//todo, remove
	UE_LOG(LogTemp, Warning, TEXT("Dist=%.0f T=%.2f FleeWeight=%.2f Close=%.0f Far=%.0f"),
	Distance,
	(Distance - CloseFleeDistance) / (FarFleeDistance - CloseFleeDistance),
	FleeWeight,
	CloseFleeDistance,
	FarFleeDistance);
	
	// Enable the rotation towards the zombie
	BB.SetAutoOrientToVelocity(false);
	
	auto* Face = Steering->GetFace();
	if (!Face)
		return EBTNodeResult::Failed;
	
	FTargetData ZombieTarget{};
	ZombieTarget.Position = FVector2D{(*ClosestZombie)->GetActorLocation()};
	
	Face->SetTarget(ZombieTarget);
	Flee->SetTarget(ZombieTarget);
	
	return EBTNodeResult::Succeeded;
}
