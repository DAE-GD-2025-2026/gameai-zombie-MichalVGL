// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveToClosestHouseVangeloovenMichal.h"

#include "VangeloovenMichalZombieRuntime/Survivor/SurvivorBlackboardVangeloovenMichal.h"

UMoveToClosestHouseVangeloovenMichal::UMoveToClosestHouseVangeloovenMichal()
{
	NodeName = "MoveToClosestHouse";
}

EBTNodeResult::Type UMoveToClosestHouseVangeloovenMichal::ExecuteTask(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory)
{
	SurvivorBlackboardVangeloovenMichal bb{OwnerComp.GetBlackboardComponent()};
	
	if (!bb.Blackboard)
		return EBTNodeResult::Failed;
	
	UHousesVangeloovenMichal* SeenHouses = bb.GetSeenHouses();
	if (!SeenHouses)
		return EBTNodeResult::Failed;
	
	FVector SurvivorPos = bb.GetActor()->GetActorLocation();
	auto itemIt = std::ranges::min_element(SeenHouses->Houses, std::ranges::less{}, [&](AHouse* pHouse) -> float
	{
		return FVector::DistSquared(pHouse->ActorToWorld().GetLocation(), SurvivorPos);
	});
	
	if (itemIt != SeenHouses->Houses.end())
	{
		bb.SetMoveTargetLocation((*itemIt)->ActorToWorld().GetLocation());
		bb.SetCurrentTargetType(ETargetTypeVangeloovenMichal::House);
		bb.SetCurrentTargetObject(*itemIt);
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}
