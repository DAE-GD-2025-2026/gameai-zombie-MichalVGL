#pragma once

#include "CoreMinimal.h"
#include "SteeringHelpersVangeloovenMichal.generated.h"

//SteeringParams (alias TargetData)
USTRUCT(BlueprintType)
struct FSteeringParamsVangeloovenMichal final //Also used as Target for SteeringBehaviors
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D Position;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Orientation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D LinearVelocity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AngularVelocity;

	explicit FSteeringParamsVangeloovenMichal(const FVector2D& position = FVector2D::ZeroVector, float orientation = 0.f, 
	                         const FVector2D& linearVel = FVector2D::ZeroVector, float angularVel = 0.f) :
		Position(position),
		Orientation(orientation),
		LinearVelocity(linearVel),
		AngularVelocity(angularVel)
	{}

#pragma region Functions
	void Clear()
	{
		Position = FVector2D::ZeroVector;
		LinearVelocity = FVector2D::ZeroVector;

		Orientation = 0.f;
		AngularVelocity = 0.f;
	}
#pragma endregion

#pragma region Operator Overloads
	FSteeringParamsVangeloovenMichal(const FSteeringParamsVangeloovenMichal& other)
	{
		Position = other.Position;
		Orientation = other.Orientation;
		LinearVelocity = other.LinearVelocity;
		AngularVelocity = other.AngularVelocity;
	}

	FSteeringParamsVangeloovenMichal& operator=(const FSteeringParamsVangeloovenMichal& other)
	{
		Position = other.Position;
		Orientation = other.Orientation;
		LinearVelocity = other.LinearVelocity;
		AngularVelocity = other.AngularVelocity;

		return *this;
	}

	bool operator==(const FSteeringParamsVangeloovenMichal& other) const
	{
		return Position == other.Position && Orientation == other.Orientation && LinearVelocity == other.LinearVelocity && AngularVelocity == other.AngularVelocity;
	}

	bool operator!=(const FSteeringParamsVangeloovenMichal& other) const
	{
		return Position != other.Position || Orientation != other.Orientation || LinearVelocity != other.LinearVelocity || AngularVelocity != other.AngularVelocity;
	}
#pragma endregion

};
using FTargetData = FSteeringParamsVangeloovenMichal; //Alias for SteeringBehavior usage ( Bit clearer in its context ;) )

struct SteeringOutputVangeloovenMichal final
{
	FVector2D LinearVelocity{};
	float AngularVelocity{0.f};
	bool IsValid{true};

	SteeringOutputVangeloovenMichal(const FVector2D& linearVelocity = {0.f, 0.f}, float angularVelocity = {0.f})
	{
		LinearVelocity = linearVelocity;
		AngularVelocity = angularVelocity;
	}

	SteeringOutputVangeloovenMichal& operator=(const SteeringOutputVangeloovenMichal& other)
	{
		LinearVelocity = other.LinearVelocity;
		AngularVelocity = other.AngularVelocity;
		IsValid = other.IsValid;

		return *this;
	}

	SteeringOutputVangeloovenMichal& operator+(const SteeringOutputVangeloovenMichal& other)
	{
		LinearVelocity += other.LinearVelocity;
		AngularVelocity += other.AngularVelocity;

		return *this;
	}

	SteeringOutputVangeloovenMichal& operator*=(const SteeringOutputVangeloovenMichal& other)
	{
		LinearVelocity = LinearVelocity * other.LinearVelocity;
		AngularVelocity = AngularVelocity * other.AngularVelocity;

		return *this;
	}

	SteeringOutputVangeloovenMichal& operator*=(float f)
	{
		LinearVelocity = f * LinearVelocity;
		AngularVelocity = f * AngularVelocity;

		return *this;
	}

	SteeringOutputVangeloovenMichal& operator/=(float f)
	{
		LinearVelocity = LinearVelocity / f;
		AngularVelocity = AngularVelocity / f;

		return *this;
	}
};
