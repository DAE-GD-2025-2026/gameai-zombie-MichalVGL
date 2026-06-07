// Fill out your copyright notice in the Description page of Project Settings.


#include "KillOrRunVangeloovenMichal.h"

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
	
	// Calculate the weights based on the closest zombie

	auto ClosestZombie = std::ranges::min_element(Zombies->Zombies, std::ranges::less{}, [&](const ABaseZombie* Zombie)
	{
		return FVector::DistSquared(Zombie->GetActorLocation(), Self->GetActorLocation());
	});

	if (ClosestZombie == std::ranges::end(Zombies->Zombies))
	{
		return EBTNodeResult::Failed;
	}
	
	//if we have a weapon, shoot
	// otherwise enable sprint.
	
	//if we shot and killed the zombie, disable sprint
	
	//todo add shooting 
	
	return EBTNodeResult::Succeeded;
}