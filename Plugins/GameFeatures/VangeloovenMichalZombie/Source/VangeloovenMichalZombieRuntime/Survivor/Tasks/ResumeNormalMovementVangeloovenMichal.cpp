// Fill out your copyright notice in the Description page of Project Settings.


#include "ResumeNormalMovementVangeloovenMichal.h"

#include "VangeloovenMichalZombieRuntime/Survivor/SurvivorBlackboardVangeloovenMichal.h"

UResumeNormalMovementVangeloovenMichal::UResumeNormalMovementVangeloovenMichal()
{
	NodeName = "ResumeNormalMovement";
}

EBTNodeResult::Type UResumeNormalMovementVangeloovenMichal::ExecuteTask(UBehaviorTreeComponent& OwnerComp,
                                                                        uint8* NodeMemory)
{
	SurvivorBlackboardVangeloovenMichal BB{OwnerComp.GetBlackboardComponent()};

	auto* Steering = BB.GetSteeringBehavior();
	if (!Steering)
		return EBTNodeResult::Failed;
	
	auto* Flee = Steering->GetFlee();
	auto* MoveTo = Steering->GetMoveTo();
	
	auto* MainMoveBlend = Steering->GetMoveBehavior();
	auto* MainLookBehavior = Steering->GetLookBehavior();
	
	if (!MoveTo || !Flee
		|| !MainMoveBlend
		|| !MainLookBehavior)
		return EBTNodeResult::Failed;
	
	MainMoveBlend->SetWeight(Flee, 0.f);
	MainMoveBlend->SetWeight(MoveTo, 1.f);
	
	// Enable the rotation towards the zombie
	BB.SetAutoOrientToVelocity(true);
	BB.SetEngageZombie(false);
	
	ASurvivorPawn* Survivor = Cast<ASurvivorPawn>(BB.GetActor());
	if (!Survivor)
		return EBTNodeResult::Failed;
	
	Survivor->StopRunning();
	
	return EBTNodeResult::Succeeded;
}
