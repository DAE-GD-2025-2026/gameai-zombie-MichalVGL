

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TargetTypesVangeloovenMichal.generated.h"

UENUM(BlueprintType)
enum class ETargetTypeVangeloovenMichal : uint8
{
	Null = 0 UMETA(DisplayName = "Null"),
	Item = 1 UMETA(DisplayName = "Item"),
	House = 2 UMETA(DisplayName = "House"),
	WanderSpot = 3 UMETA(DisplayName = "WanderSpot")
};