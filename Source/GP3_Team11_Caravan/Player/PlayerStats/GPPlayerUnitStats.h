#pragma once
#include "GPPlayerUnitStats.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class UGPPlayerUnitStats : public UActorComponent
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	int UnitIndex;
	
	UPROPERTY(EditAnywhere)
	float speedModifier = 0.6f;
	UPROPERTY(EditAnywhere)
	float healthModifier = 0.5f;
	UPROPERTY(EditAnywhere)
	float damageModifier = 0.1f;

	float GetSpeedModifier();
	float GetHealthModifier();
	float GetDamageModifier();

	void SetSpeedModifier(float value);
	void SetHealthModifier(float value);
	void SetDamageModifier(float value);
};
