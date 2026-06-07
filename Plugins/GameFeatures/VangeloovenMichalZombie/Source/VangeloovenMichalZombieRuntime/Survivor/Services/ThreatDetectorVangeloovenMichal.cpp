// Fill out your copyright notice in the Description page of Project Settings.


#include "ThreatDetectorVangeloovenMichal.h"

#include <Programs/UnrealBuildAccelerator/Core/Public/UbaBase.h>

#include "AIController.h"
#include "VangeloovenMichalZombieRuntime/Survivor/SurvivorBlackboardVangeloovenMichal.h"
#include "VangeloovenMichalZombieRuntime/ZombieExtension/ZombieBlackboardVangeloovenMichal.h"

void UThreatDetectorVangeloovenMichal::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
                                                float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	SurvivorBlackboardVangeloovenMichal BB{OwnerComp.GetBlackboardComponent()};

	if (!BB.Blackboard)
		return;

	UZombiesVangeloovenMichal* ThreatZombies = BB.GetThreateningZombies();
	if (!ThreatZombies)
	{
		ThreatZombies = NewObject<UZombiesVangeloovenMichal>();
		BB.SetThreateningZombies(ThreatZombies);
	}
	ThreatZombies->Zombies.clear();
	
	if (!BB.GetSeenZombies())
		return;
	
	//clean up seen zombies
	if (auto* SeenZombies = BB.GetSeenZombies())
	{
		std::erase_if(SeenZombies->Zombies, [](ABaseZombie* Z)
		{
			return !IsValid(Z);
		});
	}
	
	//add if they threaten the survivor
	std::ranges::for_each(BB.GetSeenZombies()->Zombies, [&](ABaseZombie* Zombie)
	{
		if (!IsValid(Zombie)) 
			return;
		
		AAIController* AIC = Cast<AAIController>(Zombie->GetController());
		if (!AIC) 
			return;
		
		ZombieBlackboardVangeloovenMichal ZBB{AIC->GetBlackboardComponent()};
		if (!ZBB.Blackboard) 
			return;
		
		float DistanceToSurvivor = FVector::Dist(ZBB.GetActor()->GetActorLocation(), BB.GetActor()->GetActorLocation());
		
		if (ZBB.GetSurvivor() && DistanceToSurvivor < MaxDistance) //survivor is set -> zombie is chasing the survivor
		{
			ThreatZombies->Zombies.push_back(Zombie);
		}
	});
}
