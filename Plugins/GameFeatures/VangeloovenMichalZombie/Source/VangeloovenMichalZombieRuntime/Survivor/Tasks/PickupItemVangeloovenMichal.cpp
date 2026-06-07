// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupItemVangeloovenMichal.h"

#include "Common/InventoryComponent.h"
#include "VangeloovenMichalZombieRuntime/Survivor/IdealInventoryVangeloovenMichal.h"
#include "VangeloovenMichalZombieRuntime/Survivor/SurvivorBlackboardVangeloovenMichal.h"

UPickupItemVangeloovenMichal::UPickupItemVangeloovenMichal()
{
	NodeName = "PickupItem";
}

EBTNodeResult::Type UPickupItemVangeloovenMichal::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	SurvivorBlackboardVangeloovenMichal BB{OwnerComp.GetBlackboardComponent()};
	
	ABaseItem* Item = Cast<ABaseItem>(BB.GetCurrentTargetObject());
	if (!Item || !IsValid(Item))
		return EBTNodeResult::Failed;
	
	UInventoryComponent* InventoryComp = BB.GetActor()->GetComponentByClass<UInventoryComponent>();
	if (!InventoryComp)
		return EBTNodeResult::Failed;

	auto& Inventory = InventoryComp->GetInventory();
	
	int Index = std::invoke([&]() -> int
	{
		for (int i{}; i < Inventory.Num(); ++i)
		{
			if (Inventory[i] == nullptr //nothing assigned
				&& ItemToBaseItemType(Item->GetItemType()) == g_IdealInventory[i]) //slot is for that type
			{
				return i;
			}
		}
		
		return -1;
	});
	
	if (Index == -1)
	{
		BB.SetCurrentTargetObject(nullptr);
		BB.SetCurrentTargetType(ETargetTypeVangeloovenMichal::Null);
		return EBTNodeResult::Failed;
	}
	
	InventoryComp->GrabItem(Index, Item);
	InventoryComp->UseItem(Index);

	if (auto* SeenItems = BB.GetSeenItems())
	{
		std::erase(SeenItems->Items, Item);
	}
	
	BB.SetCurrentTargetObject(nullptr);
	BB.SetCurrentTargetType(ETargetTypeVangeloovenMichal::Null);
	
	return EBTNodeResult::Succeeded;
}
