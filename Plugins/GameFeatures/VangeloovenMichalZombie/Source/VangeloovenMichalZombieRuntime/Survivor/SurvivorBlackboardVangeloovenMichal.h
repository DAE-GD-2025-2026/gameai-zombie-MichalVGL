// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <vector>

#include "CoreMinimal.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Items/BaseItem.h"
#include "UObject/Object.h"
#include "VangeloovenMichalZombieRuntime/Utils/BlackboardExtensionsVangeloovenMichal.h"
#include "VangeloovenMichalZombieRuntime/Utils/TargetTypesVangeloovenMichal.h"
#include "Village/House/House.h"
#include "Zombies/BaseZombie.h"

#include "SurvivorBlackboardVangeloovenMichal.generated.h"

// =====================================================
// Keys
// =====================================================

namespace SurvivorBBItemsVangeloovenMichal
{
	inline const FName Actor{"SelfActor"};
	inline const FName SeenItems{"SeenItems"};
	inline const FName SeenHouses{"SeenHouses"};
	inline const FName SeenZombies{"SeenZombies"};
	inline const FName ThreateningZombies{"ThreateningZombies"};
	inline const FName MoveTargetLocation{"MoveTargetLocation"};
	inline const FName CurrentTargetType{"CurrentTargetType"};
	inline const FName CurrentTargetObject{"CurrentTargetObject"};
	inline const FName ClearedHouses{"ClearedHouses"};
}

// =====================================================
// Blackboard custom data
// =====================================================

UCLASS()
class VANGELOOVENMICHALZOMBIERUNTIME_API UItemsVangeloovenMichal : public UObject
{
	GENERATED_BODY()

public:
	std::vector<ABaseItem*> Items{};
};

UCLASS()
class VANGELOOVENMICHALZOMBIERUNTIME_API UHousesVangeloovenMichal : public UObject
{
	GENERATED_BODY()

public:
	std::vector<AHouse*> Houses{};
};

UCLASS()
class VANGELOOVENMICHALZOMBIERUNTIME_API UZombiesVangeloovenMichal : public UObject
{
	GENERATED_BODY()

public:
	std::vector<ABaseZombie*> Zombies{};
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

	// --- Seen Items ---
	UItemsVangeloovenMichal* GetSeenItems() const
	{
		return Cast<UItemsVangeloovenMichal>(
			Blackboard->GetValue<UBlackboardKeyType_TrackedObjectVangeloovenMichal>(
				SurvivorBBItemsVangeloovenMichal::SeenItems));
	}

	void SetSeenItems(UItemsVangeloovenMichal* Objects) const
	{
		Blackboard->SetValue<UBlackboardKeyType_TrackedObjectVangeloovenMichal>(
			SurvivorBBItemsVangeloovenMichal::SeenItems, Objects);
	}

	// --- Seen Houses ---
	UHousesVangeloovenMichal* GetSeenHouses() const
	{
		return Cast<UHousesVangeloovenMichal>(
			Blackboard->GetValue<UBlackboardKeyType_TrackedObjectVangeloovenMichal>(
				SurvivorBBItemsVangeloovenMichal::SeenHouses));
	}

	void SetSeenHouses(UHousesVangeloovenMichal* Houses) const
	{
		Blackboard->SetValue<UBlackboardKeyType_TrackedObjectVangeloovenMichal>(
			SurvivorBBItemsVangeloovenMichal::SeenHouses, Houses);
	}

	// --- Seen Zombies ---
	UZombiesVangeloovenMichal* GetSeenZombies() const
	{
		return Cast<UZombiesVangeloovenMichal>(
			Blackboard->GetValue<UBlackboardKeyType_TrackedObjectVangeloovenMichal>(
				SurvivorBBItemsVangeloovenMichal::SeenZombies));
	}

	void SetSeenZombies(UZombiesVangeloovenMichal* Zombies) const
	{
		Blackboard->SetValue<UBlackboardKeyType_TrackedObjectVangeloovenMichal>(
			SurvivorBBItemsVangeloovenMichal::SeenZombies, Zombies);
	}

	// --- Threatening Zombies ---
	UZombiesVangeloovenMichal* GetThreateningZombies() const
	{
		return Cast<UZombiesVangeloovenMichal>(
			Blackboard->GetValue<UBlackboardKeyType_TrackedObjectVangeloovenMichal>(
				SurvivorBBItemsVangeloovenMichal::ThreateningZombies));
	}

	void SetThreateningZombies(UZombiesVangeloovenMichal* Zombies) const
	{
		Blackboard->SetValue<UBlackboardKeyType_TrackedObjectVangeloovenMichal>(
			SurvivorBBItemsVangeloovenMichal::ThreateningZombies, Zombies);
	}

	// --- Move Target Location ---
	FVector GetMoveTargetLocation() const
	{
		return Blackboard->GetValueAsVector(SurvivorBBItemsVangeloovenMichal::MoveTargetLocation);
	}

	void SetMoveTargetLocation(const FVector& Location) const
	{
		Blackboard->SetValueAsVector(SurvivorBBItemsVangeloovenMichal::MoveTargetLocation, Location);
	}

	// --- Current Target Type ---
	ETargetTypeVangeloovenMichal GetCurrentTargetType() const
	{
		return static_cast<ETargetTypeVangeloovenMichal>(
			Blackboard->GetValueAsInt(SurvivorBBItemsVangeloovenMichal::CurrentTargetType)
		);
	}

	void SetCurrentTargetType(ETargetTypeVangeloovenMichal Type) const
	{
		Blackboard->SetValueAsInt(SurvivorBBItemsVangeloovenMichal::CurrentTargetType, static_cast<int>(Type));
	}
	
	// --- Current Target Object ---
	UObject* GetCurrentTargetObject() const
	{
		return Blackboard->GetValueAsObject(SurvivorBBItemsVangeloovenMichal::CurrentTargetObject);
	}

	void SetCurrentTargetObject(UObject* Object) const
	{
		Blackboard->SetValueAsObject(SurvivorBBItemsVangeloovenMichal::CurrentTargetObject, Object);
	}
	
	// --- Cleared Houses ---
	UHousesVangeloovenMichal* GetClearedHouses() const
	{
		return Cast<UHousesVangeloovenMichal>(
			Blackboard->GetValue<UBlackboardKeyType_TrackedObjectVangeloovenMichal>(
				SurvivorBBItemsVangeloovenMichal::ClearedHouses));
	}

	void SetClearedHouses(UHousesVangeloovenMichal* Houses) const
	{
		Blackboard->SetValue<UBlackboardKeyType_TrackedObjectVangeloovenMichal>(
			SurvivorBBItemsVangeloovenMichal::ClearedHouses, Houses);
	}
};
