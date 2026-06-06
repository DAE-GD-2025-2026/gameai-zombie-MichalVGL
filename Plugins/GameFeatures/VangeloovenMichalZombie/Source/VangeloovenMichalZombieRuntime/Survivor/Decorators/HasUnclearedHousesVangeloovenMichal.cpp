// Fill out your copyright notice in the Description page of Project Settings.


#include "HasUnclearedHousesVangeloovenMichal.h"

#include "VangeloovenMichalZombieRuntime/Survivor/SurvivorBlackboardVangeloovenMichal.h"

bool UHasUnclearedHousesVangeloovenMichal::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
                                                                      uint8* NodeMemory) const
{
	SurvivorBlackboardVangeloovenMichal bb{OwnerComp.GetBlackboardComponent()};
	
	if (!bb.Blackboard
		|| !bb.GetSeenHouses())
		return false;
	
	return bb.GetSeenHouses()->Houses.size() > 0;
}
