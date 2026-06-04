// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "Items/ItemType.h"

#include "HasSeenItemVangeloovenMichal.generated.h"

/**
 * 
 */
UCLASS()
class VANGELOOVENMICHALZOMBIERUNTIME_API UHasSeenItemVangeloovenMichal : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UHasSeenItemVangeloovenMichal();
	
protected:
	
	//todo, move to a blackboard request item
	UPROPERTY(EditAnywhere, Category = "Type")
	EItemType Type;
	
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
