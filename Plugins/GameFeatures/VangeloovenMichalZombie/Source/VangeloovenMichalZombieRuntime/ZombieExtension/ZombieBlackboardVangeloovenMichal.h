// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BlackboardComponent.h"

namespace ZombieBBItemsVangeloovenMichal
{
	inline const FName Actor{"SelfActor"};
	inline const FName Survivor{"Survivor"};
	inline const FName WanderSpot{"WanderSpot"};
}

struct ZombieBlackboardVangeloovenMichal
{
	ZombieBlackboardVangeloovenMichal(UBlackboardComponent* blackboard)
			: Blackboard{blackboard}
	{
	}
	
	UBlackboardComponent* Blackboard;
	
	// --- SelfActor ---
	AActor* GetActor() const
	{
		return Cast<AActor>(Blackboard->GetValueAsObject(ZombieBBItemsVangeloovenMichal::Actor));
	}

	void SetActor(AActor* Actor) const
	{
		Blackboard->SetValueAsObject(ZombieBBItemsVangeloovenMichal::Actor, Actor);
	}
	// --- Survivor ---
	AActor* GetSurvivor() const
	{
		return Cast<AActor>(Blackboard->GetValueAsObject(ZombieBBItemsVangeloovenMichal::Actor));
	}

	void SetSurvivor(AActor* Survivor) const
	{
		Blackboard->SetValueAsObject(ZombieBBItemsVangeloovenMichal::Survivor, Survivor);
	}
	
	// --- Wander Spot ---
	FVector GetWanderSpot() const
	{
		return Blackboard->GetValueAsVector(ZombieBBItemsVangeloovenMichal::WanderSpot);
	}

	void SetWanderSpot(const FVector& WanderSpot) const
	{
		Blackboard->SetValueAsVector(ZombieBBItemsVangeloovenMichal::WanderSpot, WanderSpot);
	}
};