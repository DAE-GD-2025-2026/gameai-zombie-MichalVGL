// Fill out your copyright notice in the Description page of Project Settings.


#include "HasSeenItemVangeloovenMichal.h"

#include "VangeloovenMichalZombieRuntime/Survivor/SurvivorBlackboardVangeloovenMichal.h"

UHasSeenItemVangeloovenMichal::UHasSeenItemVangeloovenMichal()
{
	NodeName = "HasSeenItem";
}

bool UHasSeenItemVangeloovenMichal::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory) const
{
	SurvivorBlackboardVangeloovenMichal bb{OwnerComp.GetBlackboardComponent()};
	
	if (!bb.Blackboard 
		|| !bb.GetSeenItems())
		return false;
	
	return std::ranges::any_of(bb.GetSeenItems()->Items, [&](ABaseItem* pItem) -> bool
	{
		if (pItem)
		{
			return pItem->GetItemType() == Type;
		}
		
		return false;
	});
}
