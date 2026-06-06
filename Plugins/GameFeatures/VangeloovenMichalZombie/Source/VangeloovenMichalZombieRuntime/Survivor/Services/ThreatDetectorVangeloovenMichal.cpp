// Fill out your copyright notice in the Description page of Project Settings.


#include "ThreatDetectorVangeloovenMichal.h"

#include "AIController.h"
#include "VangeloovenMichalZombieRuntime/Survivor/SurvivorBlackboardVangeloovenMichal.h"
#include "VangeloovenMichalZombieRuntime/ZombieExtension/ZombieBlackboardVangeloovenMichal.h"

void UThreatDetectorVangeloovenMichal::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
                                                float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	SurvivorBlackboardVangeloovenMichal bb{OwnerComp.GetBlackboardComponent()};

	if (!bb.Blackboard)
		return;

	UZombiesVangeloovenMichal* ThreatZombies = bb.GetThreateningZombies();
	if (!ThreatZombies)
	{
		ThreatZombies = NewObject<UZombiesVangeloovenMichal>();
		bb.SetThreateningZombies(ThreatZombies);
	}
	ThreatZombies->Zombies.clear();
	
	if (!bb.GetSeenZombies())
		return;
	
	std::ranges::for_each(bb.GetSeenZombies()->Zombies, [&](ABaseZombie* Zombie)
	{
		AAIController* AIC = Cast<AAIController>(Zombie->GetController());
		if (!AIC) 
			return;
		
		ZombieBlackboardVangeloovenMichal bb{AIC->GetBlackboardComponent()};
		
		if (bb.GetSurvivor()) //survivor is set -> zombie is chasing the survivor
		{
			ThreatZombies->Zombies.push_back(Zombie);
		}
	});
}
