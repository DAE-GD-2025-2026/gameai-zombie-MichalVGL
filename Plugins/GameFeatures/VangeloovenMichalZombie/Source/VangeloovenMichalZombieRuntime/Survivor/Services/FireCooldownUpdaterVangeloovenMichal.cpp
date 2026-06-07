// Fill out your copyright notice in the Description page of Project Settings.


#include "FireCooldownUpdaterVangeloovenMichal.h"

#include "VangeloovenMichalZombieRuntime/Survivor/SurvivorBlackboardVangeloovenMichal.h"

UFireCooldownUpdaterVangeloovenMichal::UFireCooldownUpdaterVangeloovenMichal()
{
	NodeName = "UFireCooldownUpdater";
}

void UFireCooldownUpdaterVangeloovenMichal::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
                                                     float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	SurvivorBlackboardVangeloovenMichal BB{OwnerComp.GetBlackboardComponent()};
	if (!BB.Blackboard)
		return;
	
	float Current = BB.GetFireCooldown();
	if (Current > 0.f)
	{
		Current -= DeltaSeconds;
		BB.SetFireCooldown(Current);
	}
}
