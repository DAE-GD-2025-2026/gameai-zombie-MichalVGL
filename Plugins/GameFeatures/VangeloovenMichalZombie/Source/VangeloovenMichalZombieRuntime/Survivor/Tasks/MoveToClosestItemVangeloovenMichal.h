// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Items/ItemType.h"
#include "MoveToClosestItemVangeloovenMichal.generated.h"

/**
 * 
 */
UCLASS()
class VANGELOOVENMICHALZOMBIERUNTIME_API UMoveToClosestItemVangeloovenMichal : public UBTTaskNode
{
	GENERATED_BODY()

public:
	
	//todo, move to a blackboard request item
	UPROPERTY(EditAnywhere, Category = "Type")
	EItemType Type;

	UMoveToClosestItemVangeloovenMichal();
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
