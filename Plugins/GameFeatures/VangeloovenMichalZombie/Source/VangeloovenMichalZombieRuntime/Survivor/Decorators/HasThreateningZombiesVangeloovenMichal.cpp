// Fill out your copyright notice in the Description page of Project Settings.


#include "HasThreateningZombiesVangeloovenMichal.h"

#include "VangeloovenMichalZombieRuntime/Survivor/SurvivorBlackboardVangeloovenMichal.h"

bool UHasThreateningZombiesVangeloovenMichal::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
                                                                         uint8* NodeMemory) const
{
	SurvivorBlackboardVangeloovenMichal bb{OwnerComp.GetBlackboardComponent()};
	
	if (!bb.Blackboard
		|| !bb.GetThreateningZombies())
		return false;
	
	return bb.GetThreateningZombies()->Zombies.size() > 0;
}
