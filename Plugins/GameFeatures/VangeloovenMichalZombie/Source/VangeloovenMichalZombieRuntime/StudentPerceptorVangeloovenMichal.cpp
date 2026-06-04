// Fill out your copyright notice in the Description page of Project Settings.


#include "StudentPerceptorVangeloovenMichal.h"

#include "AIController.h"
#include "Utils/LoggerVangeloovenMichal.h"

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
		PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(
			this, &UStudentPerceptorVangeloovenMichal::OnPerceptionUpdated);
	}

	if (InventoryComponent = GetOwner()->FindComponentByClass<UInventoryComponent>()
		; !InventoryComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("[StudentPerceptor] No inventory component found"));
	}

	APawn* Pawn = Cast<APawn>(GetOwner());
	if (!Pawn) return;

	AAIController* AIController = Cast<AAIController>(Pawn->GetController());
	if (!AIController)
	{
		Logger::Console(TEXT("[StudentPerceptor] No aicontroller on the owner."));
		return;
	}

	//SurvivorBlackboardVangeloovenMichal bb{AIController->GetBlackboardComponent()};

	//bb.SetSeenItems(NewObject<USeenItemsVangeloovenMichal>(this));
}

void UStudentPerceptorVangeloovenMichal::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	Logger::Screen(TEXT("Saw Something!"));

	APawn* Pawn = Cast<APawn>(GetOwner());
	if (!Pawn) return;

	AAIController* AIController = Cast<AAIController>(Pawn->GetController());
	if (!AIController)
	{
		Logger::Console(TEXT("[StudentPerceptor] No aicontroller on the owner."));
		return;
	}

	SurvivorBlackboardVangeloovenMichal bb{AIController->GetBlackboardComponent()};

	if (auto* pItem = Cast<ABaseItem>(Actor)
		; pItem)
	{
		Logger::Screen(TEXT("Saw Item"));

		//InventoryComponent->GrabItem(0, pItem);

		if (bb.Blackboard)
		{
			auto* SeenObjects = bb.GetSeenItems();

			if (!SeenObjects)
			{
				SeenObjects = NewObject<USeenItemsVangeloovenMichal>(this);
				bb.SetSeenItems(SeenObjects);
			}

			if (std::ranges::find(SeenObjects->Items, pItem) == std::ranges::end(SeenObjects->Items))
			{
				SeenObjects->Items.push_back(pItem);
			}

			UE_LOG(LogTemp, Warning, TEXT("[StudentPerceptor] SeenObjects size: %i"),
			       static_cast<int>(SeenObjects->Items.size()))
			
			std::ranges::for_each(SeenObjects->Items, [&](auto p)
			{
				UE_LOG(LogTemp, Warning, TEXT("Item: %s"), *UEnum::GetValueAsString(p->GetItemType()));
			});
		}
	}
}
