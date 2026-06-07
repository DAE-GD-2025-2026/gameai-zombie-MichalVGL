// Fill out your copyright notice in the Description page of Project Settings.


#include "KillOrRunVangeloovenMichal.h"

#include "Common/InventoryComponent.h"
#include "VangeloovenMichalZombieRuntime/Steering/SurvivorSteeringComponentVangeloovenMichal.h"
#include "VangeloovenMichalZombieRuntime/Survivor/SurvivorBlackboardVangeloovenMichal.h"

UKillOrRunVangeloovenMichal::UKillOrRunVangeloovenMichal()
{
	NodeName = "KillOrRun";
}

EBTNodeResult::Type UKillOrRunVangeloovenMichal::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	SurvivorBlackboardVangeloovenMichal BB{OwnerComp.GetBlackboardComponent()};

	UZombiesVangeloovenMichal* Zombies = BB.GetThreateningZombies();
	if (Zombies == nullptr)
		return EBTNodeResult::Failed;

	AActor* Self = BB.GetActor();
	
	auto ClosestZombie = std::ranges::min_element(Zombies->Zombies, std::ranges::less{}, [&](const ABaseZombie* Zombie)
	{
		return FVector::DistSquared(Zombie->GetActorLocation(), Self->GetActorLocation());
	});

	if (ClosestZombie == std::ranges::end(Zombies->Zombies))
	{
		return EBTNodeResult::Failed;
	}
	
	UInventoryComponent* InventoryComp = Self->GetComponentByClass<UInventoryComponent>();
	ASurvivorPawn* Survivor = Cast<ASurvivorPawn>(Self);
	if (!InventoryComp || !Survivor)
		return EBTNodeResult::Failed;
	
	BB.SetEngageZombie(true);
	
	// find a weapon in inventory
	auto& Inventory = InventoryComp->GetInventory();
	int WeaponIndex = -1;
	for (int i{}; i < Inventory.Num(); ++i)
	{
		if (!Inventory[i]) continue;
		const EItemType Type = Inventory[i]->GetItemType();
		if (Type == EItemType::Shotgun || Type == EItemType::Pistol)
		{
			WeaponIndex = i;
			break;
		}
	}

	if (WeaponIndex != -1) //has weapon, shoot
	{
		Survivor->StopRunning();
		
		// check if pawn is facing the zombie before shooting
		const FVector ToZombie = ((*ClosestZombie)->GetActorLocation() 
								 - Survivor->GetActorLocation()).GetSafeNormal();
		const float Dot = FVector::DotProduct(Survivor->GetActorForwardVector(), ToZombie);
		const float AimThresholdDot = FMath::Cos(FMath::DegreesToRadians(AimThresholdDegrees));
		
		if (Dot > AimThresholdDot 
			&& BB.GetFireCooldown() < 0.001f)
		{
			InventoryComp->UseItem(WeaponIndex); // triggers shoot logic on the weapon
			if (Inventory[WeaponIndex]->GetValue() <= 0) //remove if empty
				InventoryComp->RemoveItem(WeaponIndex);
			
			BB.SetFireCooldown(WeaponCooldown);
		}
	}
	else //run
	{
		Survivor->StartRunning();
	}
	
	//engaging a zombie always fails, it should always trigger the next branch in the behavior tree
	return EBTNodeResult::Failed;
}