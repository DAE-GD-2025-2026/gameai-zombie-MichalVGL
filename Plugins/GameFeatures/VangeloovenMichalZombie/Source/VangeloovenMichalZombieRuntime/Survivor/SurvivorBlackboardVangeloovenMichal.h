// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "UObject/Object.h"

namespace my_namespace
{
	
}

namespace SurvivorBBItemsVangeloovenMichal
{
	inline const FName Actor{"SelfActor"};
	inline const FName Pickup{"Pickup"};
}

struct SurvivorBlackboardVangeloovenMichal
{
	SurvivorBlackboardVangeloovenMichal(UBlackboardComponent* blackboard)
			: Blackboard{blackboard}
	{
	}
	
	UBlackboardComponent* Blackboard;
	
	// --- SelfActor ---
	AActor* GetActor() const
	{
		return Cast<AActor>(Blackboard->GetValueAsObject(SurvivorBBItemsVangeloovenMichal::Actor));
	}

	void SetActor(AActor* Actor) const
	{
		Blackboard->SetValueAsObject(SurvivorBBItemsVangeloovenMichal::Actor, Actor);
	}
	
	// --- Pickup ---
	AActor* GetPickup() const
	{
		return Cast<AActor>(Blackboard->GetValueAsObject(SurvivorBBItemsVangeloovenMichal::Pickup));
	}

	void SetPickup(AActor* Actor) const
	{
		Blackboard->SetValueAsObject(SurvivorBBItemsVangeloovenMichal::Pickup, Actor);
	}
};
