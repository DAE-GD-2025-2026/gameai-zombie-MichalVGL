// Fill out your copyright notice in the Description page of Project Settings.


#include "ExecuteMoveToVangeloovenMichal.h"

#include "AIController.h"
#include "Survivor/SurvivorPawn.h"
#include "VangeloovenMichalZombieRuntime/Steering/SurvivorSteeringComponentVangeloovenMichal.h"
#include "VangeloovenMichalZombieRuntime/Survivor/SurvivorBlackboardVangeloovenMichal.h"

UExecuteMoveToVangeloovenMichal::UExecuteMoveToVangeloovenMichal()
{
	bNotifyTick = true;
	NodeName = "ExecuteMoveTo";
}

EBTNodeResult::Type UExecuteMoveToVangeloovenMichal::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ASurvivorPawn* Pawn = Cast<ASurvivorPawn>(OwnerComp.GetAIOwner()->GetPawn());
	if (!Pawn) 
		return EBTNodeResult::Failed;

	USurvivorSteeringComponentVangeloovenMichal* SteeringComp = 
		Pawn->FindComponentByClass<USurvivorSteeringComponentVangeloovenMichal>();
	if (!SteeringComp) 
		return EBTNodeResult::Failed;

	// set target on the move behavior and enable it
	SurvivorBlackboardVangeloovenMichal BB{ OwnerComp.GetBlackboardComponent() };
	USurvivorSteeringVangeloovenMichal* Steering = BB.GetSteeringBehavior();
	if (!Steering) 
		return EBTNodeResult::Failed;
	
	BB.SetEnableMovement(true);

	FTargetData TargetData;
	TargetData.Position = FVector2D{BB.GetMoveTargetLocation()};
	
	Steering->GetMoveTo()->SetTarget(TargetData);

	return EBTNodeResult::InProgress;
}

void UExecuteMoveToVangeloovenMichal::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	ASurvivorPawn* Pawn = Cast<ASurvivorPawn>(OwnerComp.GetAIOwner()->GetPawn());
	if (!Pawn)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}
	
	SurvivorBlackboardVangeloovenMichal BB{ OwnerComp.GetBlackboardComponent() };

	const float DistSq = FVector2D::DistSquared(
		FVector2D{ Pawn->GetActorLocation() },
		FVector2D{ BB.GetMoveTargetLocation() }
	);

	if (DistSq < AcceptanceRadiusSq)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		BB.SetEnableMovement(false);
	}
}

EBTNodeResult::Type UExecuteMoveToVangeloovenMichal::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::AbortTask(OwnerComp, NodeMemory);
}


