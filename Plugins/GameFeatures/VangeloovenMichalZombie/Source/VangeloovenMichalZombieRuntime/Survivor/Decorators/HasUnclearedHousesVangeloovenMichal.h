// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "HasUnclearedHousesVangeloovenMichal.generated.h"

/**
 * 
 */
UCLASS()
class VANGELOOVENMICHALZOMBIERUNTIME_API UHasUnclearedHousesVangeloovenMichal : public UBTDecorator
{
	GENERATED_BODY()
	
protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
