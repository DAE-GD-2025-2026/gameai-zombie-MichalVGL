// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <vector>

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "Items/BaseItem.h"
#include "ItemCollectionHandlerVangeloovenMichal.generated.h"

/**
 * 
 */

UCLASS()
class VANGELOOVENMICHALZOMBIERUNTIME_API UItemCollectionHandlerVangeloovenMichal : public UBTService
{
	GENERATED_BODY()
	
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
