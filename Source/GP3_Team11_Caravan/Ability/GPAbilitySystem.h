#pragma once

#include "CoreMinimal.h"
#include "GPAbilitySystem.generated.h"

class UNiagaraSystem;
class AActor;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class GP3_TEAM11_CARAVAN_API UGPAbilitySystem : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGPAbilitySystem();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Function handle activation
	UFUNCTION(BlueprintCallable)
	bool ActivateAbility(float scale, TArray<AActor*> targets, FVector particleSpawnLocation);

	// Played particle effect
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UNiagaraSystem* PlayedEffectSystem;

	/*Write in Minutes*/
	UPROPERTY(BlueprintReadWrite)
	float Cooldown = 1;

	UPROPERTY(BlueprintReadWrite)
	float CoolDownTimer = 0;

	// Ability name
	UPROPERTY(EditAnywhere)
	FString Name = "Unnamed Ability";

	

	// ##############################
	// ######### Stat Bonus #########
	// Health
	UPROPERTY(Category = "Stat Bonus", EditAnywhere, meta=(InlineEditConditionToggle))
	bool bAffectHealth = false;
	UPROPERTY(Category = "Stat Bonus", BlueprintReadWrite, EditAnywhere, meta=(EditCondition="bAffectHealth"))
	float HealthBonus = 0.f;

	// Movement speed
	UPROPERTY(Category = "Stat Bonus", EditAnywhere, meta=(InlineEditConditionToggle))
	bool bAffectSpeed = false;
	/*Percentage*/
	UPROPERTY(Category = "Stat Bonus", BlueprintReadWrite, EditAnywhere, meta=(EditCondition="bAffectSpeed"))
	float SpeedBonus = 0.f;
	
	
	
	// ##################################
	// ######### Action Ability #########
	// Activate
	UPROPERTY(Category="Action Ability", EditAnywhere)
	bool bActionAbility = false;

	// Range
	UPROPERTY(Category="Action Ability", BlueprintReadWrite, EditAnywhere, meta=(EditCondition="bActionAbility"))
	float Range = 300;

	/*Area of damage, gets added to range*/
	UPROPERTY(Category="Action Ability", BlueprintReadWrite, EditAnywhere, meta=(EditCondition="bActionAbility"))
	float EffectArea = 50;

	UPROPERTY(Category="Action Ability", BlueprintReadWrite, EditAnywhere, meta=(EditCondition="bActionAbility"))
	float Damage = 1;
};
