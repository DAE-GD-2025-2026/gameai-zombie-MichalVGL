// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "KillOrRunVangeloovenMichal.generated.h"

/**
 * 
 */
UCLASS()
class VANGELOOVENMICHALZOMBIERUNTIME_API UKillOrRunVangeloovenMichal : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UKillOrRunVangeloovenMichal();
	
	UPROPERTY(EditAnywhere, Category = "Attack")
	float WeaponCooldown = 0.15f;
	UPROPERTY(EditAnywhere, Category = "Attack")
	float AimThresholdDegrees = 15.f;
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
