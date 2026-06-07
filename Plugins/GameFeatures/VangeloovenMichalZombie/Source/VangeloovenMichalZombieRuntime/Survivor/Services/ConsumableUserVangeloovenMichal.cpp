// Fill out your copyright notice in the Description page of Project Settings.


#include "ConsumableUserVangeloovenMichal.h"

#include "Common/HealthComponent.h"
#include "Common/InventoryComponent.h"
#include "VangeloovenMichalZombieRuntime/Survivor/SurvivorBlackboardVangeloovenMichal.h"

void UConsumableUserVangeloovenMichal::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
                                                float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	SurvivorBlackboardVangeloovenMichal BB{OwnerComp.GetBlackboardComponent()};
	
	if (!BB.Blackboard)
		return;
	
	UHealthComponent* Health = BB.GetActor()->GetComponentByClass<UHealthComponent>();
	UStaminaComponent* Stamina = BB.GetActor()->GetComponentByClass<UStaminaComponent>();
	UInventoryComponent* InventoryComp = BB.GetActor()->GetComponentByClass<UInventoryComponent>();
	
	if (!Health || !Stamina || !InventoryComp)
		return;
	
	auto& Inventory = InventoryComp->GetInventory();
	
	int HealthMissing = Health->GetMaxHealth() - Health->GetHealth();
	float StaminaMissing = Stamina->GetMaxStamina() - Stamina->GetCurrentStamina();
	
	for (int i{}; i < Inventory.Num(); ++i)
	{
		auto Item = Inventory[i];
		if (!Item) continue;

		switch (Item->GetItemType())
		{
		case EItemType::Medkit:
			// only use if item value fits within what we're missing — no waste
			if (Item->GetValue() <= HealthMissing)
			{
				InventoryComp->UseItem(i);
				InventoryComp->RemoveItem(i);
				return; // one item per tick, re-evaluate next tick
			}
			break;

		case EItemType::Food:
			if (Item->GetValue() <= StaminaMissing)
			{
				InventoryComp->UseItem(i);
				InventoryComp->RemoveItem(i);
				return;
			}
			break;

		default:
			break;
		}
	}
}
