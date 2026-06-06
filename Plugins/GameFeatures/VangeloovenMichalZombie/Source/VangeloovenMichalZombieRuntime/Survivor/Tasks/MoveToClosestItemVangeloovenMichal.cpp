// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveToClosestItemVangeloovenMichal.h"

#include <ranges>

#include "AIController.h"
#include "VangeloovenMichalZombieRuntime/Survivor/SurvivorBlackboardVangeloovenMichal.h"

UMoveToClosestItemVangeloovenMichal::UMoveToClosestItemVangeloovenMichal()
{
	NodeName = "MoveToClosestItem";
}

EBTNodeResult::Type UMoveToClosestItemVangeloovenMichal::ExecuteTask(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory)
{
	SurvivorBlackboardVangeloovenMichal bb{OwnerComp.GetBlackboardComponent()};
	
	
	if (!bb.Blackboard)
		return EBTNodeResult::Failed;
	
	UItemsVangeloovenMichal* SeenItems = bb.GetSeenItems();
	if (!SeenItems)
		return EBTNodeResult::Failed;
	
	auto ValidItems = SeenItems->Items | std::views::filter([&](ABaseItem* pItem)
	{
		return pItem != nullptr
		&& pItem->GetItemType() == Type;
	});
	
	//============
	// Get the closest item and set the location
	
	AAIController* AI = OwnerComp.GetAIOwner();
	if (!AI) return EBTNodeResult::Failed;

	APawn* Pawn = AI->GetPawn();
	if (!Pawn) return EBTNodeResult::Failed;

	FVector SurvivorPos = Pawn->GetActorLocation();
	auto itemIt = std::ranges::min_element(ValidItems, std::ranges::less{}, [&](ABaseItem* pItem) -> float
	{
		return FVector::DistSquared(pItem->ActorToWorld().GetLocation(), SurvivorPos);
	});
	
	if (itemIt != ValidItems.end())
	{
		bb.SetMoveTargetLocation((*itemIt)->ActorToWorld().GetLocation());
		bb.SetCurrentTargetType(ETargetTypeVangeloovenMichal::Item);
		bb.SetCurrentTargetObject(*itemIt);
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}
