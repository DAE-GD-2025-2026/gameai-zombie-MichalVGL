// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Damage.h"
#include "Perception/AISense_Damage.h"
#include "GameAI_Zombie/Common/InventoryComponent.h"
#include "StudentPerceptorVangeloovenMichal.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class VANGELOOVENMICHALZOMBIERUNTIME_API UStudentPerceptorVangeloovenMichal : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UStudentPerceptorVangeloovenMichal();
	
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
	
private:
	
	UPROPERTY()
	TObjectPtr<UInventoryComponent> InventoryComponent;
	
};
