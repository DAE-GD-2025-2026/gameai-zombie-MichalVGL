#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BlackboardExtensionsVangeloovenMichal.generated.h"

//======================================
// Tracked Object
//======================================

//this key works similarly like the regular "object" 
//	but instead owns the resource and will not trigger the gc when only the blackboard holds a reference

UCLASS(EditInlineNew, meta=(DisplayName="TrackedObject"), MinimalAPI)
class UBlackboardKeyType_TrackedObjectVangeloovenMichal : public UBlackboardKeyType_Object
{
	GENERATED_UCLASS_BODY()

private:
	UPROPERTY()
	TObjectPtr<UObject> TrackedObject;

public:
	static bool SetValue(UBlackboardKeyType_TrackedObjectVangeloovenMichal* KeyOb, uint8* RawData, UObject* Value)
	{
		KeyOb->TrackedObject = Value;
		return UBlackboardKeyType_Object::SetValue(KeyOb, RawData, Value);
	}
	
	virtual void InitializeMemory(UBlackboardComponent& OwnerComp, uint8* MemoryBlock) override
	{
		TrackedObject = nullptr;
		Super::InitializeMemory(OwnerComp, MemoryBlock);
	}
};