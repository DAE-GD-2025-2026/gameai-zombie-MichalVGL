// Fill out your copyright notice in the Description page of Project Settings.


#include "StudentPerceptorVangeloovenMichal.h"

#include "AIController.h"
#include "Survivor/SurvivorBlackboardVangeloovenMichal.h"


UStudentPerceptorVangeloovenMichal::UStudentPerceptorVangeloovenMichal()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UStudentPerceptorVangeloovenMichal::BeginPlay()
{
	Super::BeginPlay();
	
	if (auto PerceptionComp = GetOwner()->GetComponentByClass<UAIPerceptionComponent>())
	{
		PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &UStudentPerceptorVangeloovenMichal::OnPerceptionUpdated);
	}
}

void UStudentPerceptorVangeloovenMichal::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Green, 
	FString::Printf(TEXT("Saw Something!")));
	
	APawn* Pawn = Cast<APawn>(GetOwner());
	if (!Pawn) return;

	AAIController* AIController = Cast<AAIController>(Pawn->GetController());
	if (AIController)
	{
		SurvivorBlackboardVangeloovenMichal bb{AIController->GetBlackboardComponent()};
		
		bb.SetPickup(Actor);\
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Green, 
	FString::Printf(TEXT("No AIController")));
	}
}
