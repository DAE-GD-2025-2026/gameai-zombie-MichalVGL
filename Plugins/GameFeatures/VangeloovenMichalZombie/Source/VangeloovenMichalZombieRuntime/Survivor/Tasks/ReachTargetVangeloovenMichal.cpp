// Fill out your copyright notice in the Description page of Project Settings.


#include "ReachTargetVangeloovenMichal.h"

#include "AIController.h"
#include "Survivor/SurvivorPawn.h"
#include "VangeloovenMichalZombieRuntime/Survivor/SurvivorBlackboardVangeloovenMichal.h"

UReachTargetVangeloovenMichal::UReachTargetVangeloovenMichal()
{
	NodeName = "ReachTarget";
}

EBTNodeResult::Type UReachTargetVangeloovenMichal::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ASurvivorPawn* Pawn = Cast<ASurvivorPawn>(OwnerComp.GetAIOwner()->GetPawn());
	if (!Pawn)
	{
		return EBTNodeResult::Failed;
	}
	
	SurvivorBlackboardVangeloovenMichal BB{ OwnerComp.GetBlackboardComponent() };

	if (BB.GetCurrentTargetType() == ETargetTypeVangeloovenMichal::Null) // no target set
		return EBTNodeResult::Failed;
	
	const float DistSq = FVector2D::DistSquared(
		FVector2D{ Pawn->GetActorLocation() },
		FVector2D{ BB.GetMoveTargetLocation() }
	);

	if (DistSq < AcceptanceRadiusSq)
	{
		BB.SetEnableMovement(false);
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}
