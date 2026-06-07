// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SurvivorSteeringComponentVangeloovenMichal.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class VANGELOOVENMICHALZOMBIERUNTIME_API USurvivorSteeringComponentVangeloovenMichal : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USurvivorSteeringComponentVangeloovenMichal();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, Category = "Steering")
	float AutoOrientInterpSpeed = 8.f;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
