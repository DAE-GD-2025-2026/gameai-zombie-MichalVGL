// Fill out your copyright notice in the Description page of Project Settings.


#include "SurvivorSteeringComponentVangeloovenMichal.h"

#include "AIController.h"
#include "Survivor/SurvivorPawn.h"
#include "VangeloovenMichalZombieRuntime/Survivor/SurvivorBlackboardVangeloovenMichal.h"
#include "VangeloovenMichalZombieRuntime/Utils/LoggerVangeloovenMichal.h"


// Sets default values for this component's properties
USurvivorSteeringComponentVangeloovenMichal::USurvivorSteeringComponentVangeloovenMichal()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USurvivorSteeringComponentVangeloovenMichal::BeginPlay()
{
	Super::BeginPlay();

	//init steering behavior
	ASurvivorPawn* Pawn = Cast<ASurvivorPawn>(GetOwner());
	if (!Pawn)
		return;

	AAIController* AIC = Cast<AAIController>(Pawn->GetController());
	if (!AIC)
		return;

	SurvivorBlackboardVangeloovenMichal BB{AIC->GetBlackboardComponent()};
	if (!BB.Blackboard)
		return;

	BB.SetSteeringBehavior(NewObject<USurvivorSteeringVangeloovenMichal>());
}


// Called every frame
void USurvivorSteeringComponentVangeloovenMichal::TickComponent(float DeltaTime, ELevelTick TickType,
                                                                FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ASurvivorPawn* Pawn = Cast<ASurvivorPawn>(GetOwner());
	if (!Pawn)
		return;

	AAIController* AIC = Cast<AAIController>(Pawn->GetController());
	if (!AIC)
		return;

	SurvivorBlackboardVangeloovenMichal BB{AIC->GetBlackboardComponent()};
	if (!BB.Blackboard)
		return;

	if (!BB.GetEnableMovement())
		return;

	USurvivorSteeringVangeloovenMichal* Steering = BB.GetSteeringBehavior();
	if (!Steering)
		return;

	auto* Move = Steering->GetMoveBehavior();
	auto* Look = Steering->GetLookBehavior();

	if (Move && Look)
	{
		const SteeringOutputVangeloovenMichal MoveOutput = Move->CalculateSteering(DeltaTime, *Pawn);
		const SteeringOutputVangeloovenMichal LookOutput = Look->CalculateSteering(DeltaTime, *Pawn);

		//Pawn->AddMovementInput(FVector{MoveOutput.LinearVelocity, 0.f});

		UFloatingPawnMovement* FloatingMovement =
			Cast<UFloatingPawnMovement>(Pawn->GetMovementComponent());

		if (FloatingMovement && !MoveOutput.LinearVelocity.IsNearlyZero())
		{
			const FVector WorldDirection = FVector{MoveOutput.LinearVelocity, 0.f};
			Pawn->AddMovementInput(WorldDirection, 1.f, true);
		}

		if (!BB.GetAutoOrientToVelocity()) //orient manually if auto orient is disabled
		{
			const bool HasLookOrientInput = !FMath::IsNearlyZero(LookOutput.AngularVelocity);
			if (HasLookOrientInput)
			{
				const float DeltaYaw{
					FMath::Clamp(LookOutput.AngularVelocity, -1.f, 1.f) * AutoOrientInterpSpeed * DeltaTime
				};

				const FRotator CurrentRotation{Pawn->GetActorRotation()};
				const FRotator DeltaRotation{0.f, DeltaYaw, 0.f};
				const FRotator DesiredRotation{CurrentRotation + DeltaRotation};

				//only yaw
				if (!FMath::IsNearlyEqual(CurrentRotation.Yaw, DesiredRotation.Yaw))
				{
					//todo, delete
					UE_LOG(LogTemp, Warning, TEXT("Rotating: current=%.1f desired=%.1f delta=%.2f"),
					       CurrentRotation.Yaw, DesiredRotation.Yaw, DeltaYaw);
					AIC->SetControlRotation((DesiredRotation));
					Pawn->FaceRotation(DesiredRotation);
				}
			}
		}
		else //orient towards velocity (auto orient)
		{
			const FVector Velocity = Pawn->GetVelocity();
			if (!Velocity.IsNearlyZero())
			{
				const FRotator TargetRotation = Velocity.GetSafeNormal().ToOrientationRotator();
				const FRotator SmoothedRotation = FMath::RInterpTo(
					Pawn->GetActorRotation(), TargetRotation, DeltaTime, AutoOrientInterpSpeed
				);
				AIC->SetControlRotation(SmoothedRotation);
				Pawn->FaceRotation(SmoothedRotation, DeltaTime);
			}
		}
	}
}
