#pragma once

namespace Logger
{
	inline void Screen(FString Text)
	{
		GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Green, 
	FString::Printf(TEXT("%s"), *Text));
	}
	
	inline void Console(FString Text)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Text);
	}
}
