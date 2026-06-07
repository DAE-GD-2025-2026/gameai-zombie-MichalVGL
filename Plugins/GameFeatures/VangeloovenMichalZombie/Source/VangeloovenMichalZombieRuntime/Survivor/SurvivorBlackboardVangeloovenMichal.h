// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <vector>
#include <memory>

#include "CoreMinimal.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Items/BaseItem.h"
#include "UObject/Object.h"
#include "VangeloovenMichalZombieRuntime/Steering/SteeringBehaviorVangeloovenMichal.h"
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
	inline const FName SteeringBehavior{"SteeringBehavior"};
	inline const FName AutoOrientToVelocity{"AutoOrient"};
	inline const FName EnableMovement{"EnableMovement"};
	inline const FName RequestedItems{"RequestedItems"};
	inline const FName FireCooldown{"FireCooldown"};
	inline const FName EngageZombie{"EngageZombie"};
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

UCLASS()
class VANGELOOVENMICHALZOMBIERUNTIME_API USurvivorSteeringVangeloovenMichal : public UObject
{
	GENERATED_BODY()

public:
	
	USurvivorSteeringVangeloovenMichal();
	
	BlendedSteeringVangeloovenMichal* GetMoveBehavior() const;
	FaceVangeloovenMichal* GetLookBehavior() const;
	
	SteeringBehaviorVangeloovenMichal* GetMoveTo() const;
	SteeringBehaviorVangeloovenMichal* GetFlee() const;
	SteeringBehaviorVangeloovenMichal* GetFace() const;
	
private:
	
	//the main steeringbehaviors
	std::unique_ptr<SteeringBehaviorVangeloovenMichal> MoveBehavior{};
	//std::unique_ptr<SteeringBehaviorVangeloovenMichal> LookBehavior{};
	
	//components used to build up the main behaviors
	std::unique_ptr<SteeringBehaviorVangeloovenMichal> MoveTo{};
	std::unique_ptr<SteeringBehaviorVangeloovenMichal> Flee{};
	std::unique_ptr<SteeringBehaviorVangeloovenMichal> Face{};
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
	
	// --- Steering Behavior ---
	USurvivorSteeringVangeloovenMichal* GetSteeringBehavior() const
	{
		return Cast<USurvivorSteeringVangeloovenMichal>(
			Blackboard->GetValue<UBlackboardKeyType_TrackedObjectVangeloovenMichal>(
				SurvivorBBItemsVangeloovenMichal::SteeringBehavior));
	}

	void SetSteeringBehavior(USurvivorSteeringVangeloovenMichal* Steering) const
	{
		Blackboard->SetValue<UBlackboardKeyType_TrackedObjectVangeloovenMichal>(
			SurvivorBBItemsVangeloovenMichal::SteeringBehavior, Steering);
	}
	
	// --- Auto Orient ---
	bool GetAutoOrientToVelocity() const
	{
		return Blackboard->GetValueAsBool(SurvivorBBItemsVangeloovenMichal::AutoOrientToVelocity);
	}

	void SetAutoOrientToVelocity(bool AutoOrient) const
	{
		Blackboard->SetValueAsBool(SurvivorBBItemsVangeloovenMichal::AutoOrientToVelocity, AutoOrient);
	}
	
	// --- Enable Movement ---
	bool GetEnableMovement() const
	{
		return Blackboard->GetValueAsBool(SurvivorBBItemsVangeloovenMichal::EnableMovement);
	}

	void SetEnableMovement(bool EnableMovement) const
	{
		Blackboard->SetValueAsBool(SurvivorBBItemsVangeloovenMichal::EnableMovement, EnableMovement);
	}
	
	// --- Requested Items ---
	UItemsVangeloovenMichal* GetRequestedItems() const
	{
		return Cast<UItemsVangeloovenMichal>(
			Blackboard->GetValue<UBlackboardKeyType_TrackedObjectVangeloovenMichal>(SurvivorBBItemsVangeloovenMichal::RequestedItems)
			);
	}

	void SetRequestedItems(UItemsVangeloovenMichal* Objects) const
	{
		Blackboard->SetValue<UBlackboardKeyType_TrackedObjectVangeloovenMichal>(SurvivorBBItemsVangeloovenMichal::RequestedItems, Objects);
	}
	
	// --- Fire Cooldown ---
	float GetFireCooldown() const
	{
		return Blackboard->GetValueAsFloat(SurvivorBBItemsVangeloovenMichal::FireCooldown);
	}

	void SetFireCooldown(float FireCooldown) const
	{
		Blackboard->SetValueAsFloat(SurvivorBBItemsVangeloovenMichal::FireCooldown, FireCooldown);
	}
	
	// --- Engage Zombie ---
	bool GetEngageZombie() const
	{
		return Blackboard->GetValueAsBool(SurvivorBBItemsVangeloovenMichal::EngageZombie);
	}

	void SetEngageZombie(bool EngageZombie) const
	{
		Blackboard->SetValueAsBool(SurvivorBBItemsVangeloovenMichal::EngageZombie, EngageZombie);
	}
};
