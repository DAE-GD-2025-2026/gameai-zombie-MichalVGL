// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveToClosestRequestedItemVangeloovenMichal.h"

#include "VangeloovenMichalZombieRuntime/Survivor/SurvivorBlackboardVangeloovenMichal.h"

UMoveToClosestRequestedItemVangeloovenMichal::UMoveToClosestRequestedItemVangeloovenMichal()
{
	NodeName = "MoveToClosestRequestedItem";
}

EBTNodeResult::Type UMoveToClosestRequestedItemVangeloovenMichal::ExecuteTask(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory)
{
	SurvivorBlackboardVangeloovenMichal bb{OwnerComp.GetBlackboardComponent()};
	
	if (!bb.Blackboard)
		return EBTNodeResult::Failed;
	
	UItemsVangeloovenMichal* RequestedItems = bb.GetRequestedItems();
	if (!RequestedItems)
		return EBTNodeResult::Failed;
	
	FVector SurvivorPos = bb.GetActor()->GetActorLocation();
	auto itemIt = std::ranges::min_element(RequestedItems->Items, std::ranges::less{}, [&](ABaseItem* Item) -> float
	{
		return FVector::DistSquared(Item->ActorToWorld().GetLocation(), SurvivorPos);
	});
	
	if (itemIt != RequestedItems->Items.end())
	{
		bb.SetMoveTargetLocation((*itemIt)->GetActorLocation());
		bb.SetCurrentTargetType(ETargetTypeVangeloovenMichal::Item);
		bb.SetCurrentTargetObject(*itemIt);
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}
