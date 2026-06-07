// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ReachTargetVangeloovenMichal.generated.h"

/**
 * 
 */
UCLASS()
class VANGELOOVENMICHALZOMBIERUNTIME_API UReachTargetVangeloovenMichal : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UReachTargetVangeloovenMichal();
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, Category = "Steering")
	float AcceptanceRadiusSq = 60.f * 60.f; // 0.6m
};
