// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemCollectionHandlerVangeloovenMichal.h"

#include <ranges>
#include <algorithm>
#include <unordered_set>

#include "Common/InventoryComponent.h"
#include "VangeloovenMichalZombieRuntime/Survivor/IdealInventoryVangeloovenMichal.h"
#include "VangeloovenMichalZombieRuntime/Survivor/SurvivorBlackboardVangeloovenMichal.h"
#include "VangeloovenMichalZombieRuntime/Utils/LoggerVangeloovenMichal.h"

void UItemCollectionHandlerVangeloovenMichal::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
                                                       float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	SurvivorBlackboardVangeloovenMichal BB{OwnerComp.GetBlackboardComponent()};

	auto* SeenItems = BB.GetSeenItems();
	if (!SeenItems)
		return;
	
	UInventoryComponent* InventoryComp = BB.GetActor()->GetComponentByClass<UInventoryComponent>();
	if (!InventoryComp)
	{
		Logger::Console(TEXT("No Inventory Component Found"));
		return;
	}

	auto& Inventory = InventoryComp->GetInventory();

	std::unordered_set<ItemBaseTypeVangeloovenMichal> NeededItems{};
	for (int i{}; i < g_IdealInventory.size(); ++i)
	{
		switch (g_IdealInventory[i])
		{
		case ItemBaseTypeVangeloovenMichal::Food:
			if (Inventory[i] == nullptr)
				NeededItems.emplace(ItemBaseTypeVangeloovenMichal::Food);
			break;
		case ItemBaseTypeVangeloovenMichal::Medkit:
			if (Inventory[i] == nullptr)
				NeededItems.emplace(ItemBaseTypeVangeloovenMichal::Medkit);
			break;
		case ItemBaseTypeVangeloovenMichal::Weapon:
		default:
			if (Inventory[i] == nullptr)
				NeededItems.emplace(ItemBaseTypeVangeloovenMichal::Weapon);
			break;
		}
	}
	
	auto* RequestedItems = BB.GetRequestedItems();
	if (!RequestedItems)
	{
		RequestedItems = NewObject<UItemsVangeloovenMichal>();
		BB.SetRequestedItems(RequestedItems);
	}

	RequestedItems->Items.clear();
	std::ranges::for_each(SeenItems->Items, [&](ABaseItem* SeenItem)
	{
		switch (SeenItem->GetItemType())
		{
		case EItemType::Food:
			if (NeededItems.contains(ItemBaseTypeVangeloovenMichal::Food))
				RequestedItems->Items.emplace_back(SeenItem);
			break;
		case EItemType::Medkit:
			if (NeededItems.contains(ItemBaseTypeVangeloovenMichal::Medkit))
				RequestedItems->Items.emplace_back(SeenItem);
			break;
		case EItemType::Shotgun:
		case EItemType::Pistol:
			if (NeededItems.contains(ItemBaseTypeVangeloovenMichal::Weapon))
				RequestedItems->Items.emplace_back(SeenItem);
			break;
		case EItemType::Garbage:
		default:
			break;
		}
	});
}
