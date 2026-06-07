// Fill out your copyright notice in the Description page of Project Settings.


#include "SurvivorBlackboardVangeloovenMichal.h"

USurvivorSteeringVangeloovenMichal::USurvivorSteeringVangeloovenMichal()
{
	MoveTo = std::make_unique<MoveToVangeloovenMichal>();
	Flee = std::make_unique<FleeVangeloovenMichal>();
	Face = std::make_unique<FaceVangeloovenMichal>();
	
	std::vector<BlendedSteeringVangeloovenMichal::WeightedBehavior> WeightedBehaviors;
	
	WeightedBehaviors.reserve(2);
	WeightedBehaviors.emplace_back(MoveTo.get(), 1.f);
	WeightedBehaviors.emplace_back(Flee.get(), 0.f);
	MoveBehavior = std::make_unique<BlendedSteeringVangeloovenMichal>(WeightedBehaviors);
	
	LookBehavior = std::make_unique<FaceVangeloovenMichal>();
}

SteeringBehaviorVangeloovenMichal* USurvivorSteeringVangeloovenMichal::GetMoveTo() const
{
	return MoveTo.get();
}

SteeringBehaviorVangeloovenMichal* USurvivorSteeringVangeloovenMichal::GetFlee() const
{
	return Flee.get();
}

SteeringBehaviorVangeloovenMichal* USurvivorSteeringVangeloovenMichal::GetFace() const
{
	return Face.get();
}
