// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "FaceClosestEnemyVangeloovenMichal.generated.h"

/**
 * 
 */
UCLASS()
class VANGELOOVENMICHALZOMBIERUNTIME_API UFaceClosestEnemyVangeloovenMichal : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UFaceClosestEnemyVangeloovenMichal();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MaxFleeInfluence = 0.8f;
	
	UPROPERTY(EditAnywhere, Category = "Movement")
	float CloseFleeDistance = 200.f; //2 meters
	
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MinFleeInfluence = 0.2f;
	
	UPROPERTY(EditAnywhere, Category = "Movement")
	float FarFleeDistance = 1000.f; //10 meters
};
