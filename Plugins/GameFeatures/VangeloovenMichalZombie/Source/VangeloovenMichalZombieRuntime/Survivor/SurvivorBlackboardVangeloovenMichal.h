// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <vector>

#include "CoreMinimal.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Items/BaseItem.h"
#include "UObject/Object.h"
#include "VangeloovenMichalZombieRuntime/Utils/BlackboardExtensionsVangeloovenMichal.h"

#include "SurvivorBlackboardVangeloovenMichal.generated.h"

// =====================================================
// Keys
// =====================================================

namespace SurvivorBBItemsVangeloovenMichal
{
	inline const FName Actor{"SelfActor"};
	inline const FName SeenItems{"SeenItems"};
	inline const FName MoveTargetLocation{"MoveTargetLocation"};
}

// =====================================================
// Blackboard custom data
// =====================================================

UCLASS()
class VANGELOOVENMICHALZOMBIERUNTIME_API USeenItemsVangeloovenMichal : public UObject
{
	GENERATED_BODY()
public:
	
	 std::vector<ABaseItem*> Items{};
};

// =====================================================
// Blackboard type helper
// =====================================================

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
	
	// --- Seen Objects ---
	USeenItemsVangeloovenMichal* GetSeenItems() const
	{
		return Cast<USeenItemsVangeloovenMichal>(Blackboard->GetValue<UBlackboardKeyType_TrackedObjectVangeloovenMichal>(SurvivorBBItemsVangeloovenMichal::SeenItems));
	}

	void SetSeenItems(USeenItemsVangeloovenMichal* Objects) const
	{
		Blackboard->SetValue<UBlackboardKeyType_TrackedObjectVangeloovenMichal>(SurvivorBBItemsVangeloovenMichal::SeenItems, Objects);
	}
	
	// --- Move Target Location ---
	FVector GetMoveTargetLocation() const
	{
		return Blackboard->GetValueAsVector(SurvivorBBItemsVangeloovenMichal::MoveTargetLocation);
	}

	void SetMoveTargetLocation(FVector Location) const
	{
		Blackboard->SetValueAsVector(SurvivorBBItemsVangeloovenMichal::MoveTargetLocation, Location);
	}
};