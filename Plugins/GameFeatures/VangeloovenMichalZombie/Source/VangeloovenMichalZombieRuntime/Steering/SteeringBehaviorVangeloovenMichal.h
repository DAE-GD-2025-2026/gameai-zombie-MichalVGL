#pragma once

#include <vector>

#include "NavigationPath.h"
#include "SteeringHelpersVangeloovenMichal.h"

class ASurvivorPawn;

// SteeringBehavior base, all steering behaviors should derive from this.
class SteeringBehaviorVangeloovenMichal
{
public:
	SteeringBehaviorVangeloovenMichal() = default;
	virtual ~SteeringBehaviorVangeloovenMichal() = default;

	// Override to implement your own behavior
	virtual SteeringOutputVangeloovenMichal CalculateSteering(float DeltaT, ASurvivorPawn& Pawn) = 0;

	void SetTarget(const FTargetData& NewTarget) { Target = NewTarget; }

	template <class T, std::enable_if_t<std::is_base_of_v<SteeringBehaviorVangeloovenMichal, T>>* = nullptr>
	T* As()
	{
		return static_cast<T*>(this);
	}

protected:
	FTargetData Target;
};

//=========================================
// Survivor implementations
//=========================================

//wrapper of the unreal engine MoveTo
class MoveToVangeloovenMichal : public SteeringBehaviorVangeloovenMichal
{
public:
	virtual ~MoveToVangeloovenMichal() override = default;

protected:
	virtual SteeringOutputVangeloovenMichal CalculateSteering(float DeltaT, ASurvivorPawn& Pawn) override;

private:
	
	float AcceptanceRadiusSq = 50.f * 50.f; //0.5m acceptance
};

//simple move away from target
class FleeVangeloovenMichal : public SteeringBehaviorVangeloovenMichal
{
public:
	virtual ~FleeVangeloovenMichal() override = default;

protected:
	virtual SteeringOutputVangeloovenMichal CalculateSteering(float DeltaT, ASurvivorPawn& Pawn) override;
};

//used for aiming at zombies
class FaceVangeloovenMichal : public SteeringBehaviorVangeloovenMichal
{
public:
	virtual ~FaceVangeloovenMichal() override = default;

protected:
	virtual SteeringOutputVangeloovenMichal CalculateSteering(float DeltaT, ASurvivorPawn& Pawn) override;
};

class BlendedSteeringVangeloovenMichal final : public SteeringBehaviorVangeloovenMichal
{
public:
	struct WeightedBehavior
	{
		SteeringBehaviorVangeloovenMichal* pBehavior = nullptr;
		float Weight = 0.f;

		WeightedBehavior(SteeringBehaviorVangeloovenMichal* const pBehavior, float Weight) :
			pBehavior(pBehavior),
			Weight(Weight)
		{
		};
	};

	BlendedSteeringVangeloovenMichal(const std::vector<WeightedBehavior>& WeightedBehaviors);

	void AddBehaviour(const WeightedBehavior& WeightedBehavior) { WeightedBehaviors.push_back(WeightedBehavior); }
	virtual SteeringOutputVangeloovenMichal CalculateSteering(float DeltaT, ASurvivorPawn& Pawn) override;

	float GetWeight(const SteeringBehaviorVangeloovenMichal* pBehavior);
	bool SetWeight(SteeringBehaviorVangeloovenMichal* pBehavior, float NewWeight);

private:
	std::vector<WeightedBehavior> WeightedBehaviors = {};
};
