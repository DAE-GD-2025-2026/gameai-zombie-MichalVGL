// Fill out your copyright notice in the Description page of Project Settings.


#include "StudentPerceptorVangeloovenMichal.h"

#include "AIController.h"
#include "Utils/LoggerVangeloovenMichal.h"

#include "Survivor/SurvivorBlackboardVangeloovenMichal.h"
#include "Village/House/House.h"


UStudentPerceptorVangeloovenMichal::UStudentPerceptorVangeloovenMichal()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UStudentPerceptorVangeloovenMichal::BeginPlay()
{
	Super::BeginPlay();

	if (auto PerceptionComp = GetOwner()->GetComponentByClass<UAIPerceptionComponent>())
	{
		PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(
			this, &UStudentPerceptorVangeloovenMichal::OnPerceptionUpdated);
	}

	if (InventoryComponent = GetOwner()->FindComponentByClass<UInventoryComponent>()
		; !InventoryComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("[StudentPerceptor] No inventory component found"));
	}

	//APawn* Pawn = Cast<APawn>(GetOwner());
	//if (!Pawn) return;
//
	//AAIController* AIController = Cast<AAIController>(Pawn->GetController());
	//if (!AIController)
	//{
	//	Logger::Console(TEXT("[StudentPerceptor] No aicontroller on the owner."));
	//	return;
	//}

	//SurvivorBlackboardVangeloovenMichal bb{AIController->GetBlackboardComponent()};

	//bb.SetSeenItems(NewObject<USeenItemsVangeloovenMichal>(this));
}

void UStudentPerceptorVangeloovenMichal::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	Logger::Screen(TEXT("Saw Something!"));

	APawn* Pawn = Cast<APawn>(GetOwner());
	if (!Pawn) return;

	AAIController* AIController = Cast<AAIController>(Pawn->GetController());
	if (!AIController)
	{
		Logger::Console(TEXT("[StudentPerceptor] No aicontroller on the owner."));
		return;
	}

	SurvivorBlackboardVangeloovenMichal bb{AIController->GetBlackboardComponent()};

	if (!bb.Blackboard)
		return;

	//add if item and unique
	if (auto* pItem = Cast<ABaseItem>(Actor))
	{
		auto* SeenItems = bb.GetSeenItems();

		if (!SeenItems)
		{
			SeenItems = NewObject<UItemsVangeloovenMichal>(this);
			bb.SetSeenItems(SeenItems);
		}

		if (std::ranges::find(SeenItems->Items, pItem) == std::ranges::end(SeenItems->Items))
		{
			SeenItems->Items.push_back(pItem);
		}
	} //add if house
	else if (auto* pHouse = Cast<AHouse>(Actor))
	{
		auto* SeenHouses = bb.GetSeenHouses();
		if (!SeenHouses)
		{
			SeenHouses = NewObject<UHousesVangeloovenMichal>(this);
			bb.SetSeenHouses(SeenHouses);
		}
		
		auto* ClearedHouses = bb.GetClearedHouses();
		if (!ClearedHouses)
		{
			ClearedHouses = NewObject<UHousesVangeloovenMichal>(this);
			bb.SetClearedHouses(ClearedHouses);
		}
		
		if (std::ranges::find(SeenHouses->Houses, pHouse) == std::ranges::end(SeenHouses->Houses)	// not in seenhouses
			&& std::ranges::find(ClearedHouses->Houses, pHouse) == std::ranges::end(ClearedHouses->Houses)) //also not cleared
		{
			SeenHouses->Houses.push_back(pHouse);
		}
	} // add if zombie
	else if (auto* pZombie = Cast<ABaseZombie>(Actor))
	{
		auto* SeenZombies = bb.GetSeenZombies();
		
		if (!SeenZombies)
		{
			SeenZombies = NewObject<UZombiesVangeloovenMichal>(this);
			bb.SetSeenZombies(SeenZombies);
		}
		
		if (std::ranges::find(SeenZombies->Zombies, pZombie) == std::ranges::end(SeenZombies->Zombies))
		{
			SeenZombies->Zombies.push_back(pZombie);
		}
	}
}
