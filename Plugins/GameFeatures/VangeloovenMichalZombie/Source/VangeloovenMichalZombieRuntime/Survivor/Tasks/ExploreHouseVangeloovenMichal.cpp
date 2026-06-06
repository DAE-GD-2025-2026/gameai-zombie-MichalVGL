// Fill out your copyright notice in the Description page of Project Settings.


#include "ExploreHouseVangeloovenMichal.h"

#include "VangeloovenMichalZombieRuntime/Survivor/SurvivorBlackboardVangeloovenMichal.h"
#include "VangeloovenMichalZombieRuntime/Utils/LoggerVangeloovenMichal.h"

UExploreHouseVangeloovenMichal::UExploreHouseVangeloovenMichal()
{
	NodeName = "ExploreHouse";
}

EBTNodeResult::Type UExploreHouseVangeloovenMichal::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	SurvivorBlackboardVangeloovenMichal bb{OwnerComp.GetBlackboardComponent()};
	
	if (!bb.Blackboard)
		return EBTNodeResult::Failed;
	
	AHouse* House = Cast<AHouse>(bb.GetCurrentTargetObject());
	
	if (!House)
	{
		Logger::Console(TEXT("[ExploreHouse] Cast failed, CurrentTargetObject is not AHouse"));
		return EBTNodeResult::Failed;
	}
	
	auto* SeenHouses = bb.GetSeenHouses();
	if (!SeenHouses)
		return EBTNodeResult::Failed;
	
	auto* ClearedHouses = bb.GetClearedHouses();
	if (!ClearedHouses)
		return EBTNodeResult::Failed;
	
	std::erase(SeenHouses->Houses, House);
	ClearedHouses->Houses.push_back(House);
	bb.SetCurrentTargetObject(nullptr);
	
	return EBTNodeResult::Succeeded;
}


