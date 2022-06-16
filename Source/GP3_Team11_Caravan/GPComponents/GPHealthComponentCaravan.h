#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GPHealthComponentCaravan.generated.h"

//Delegate to signal actor death.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCaravanDestroy, AActor*, OwningActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCaravanUpdateHealth, AActor*, OwningActor);

class UGPWidget;
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class GP3_TEAM11_CARAVAN_API UGPHealthComponentCaravan : public UActorComponent
{
	GENERATED_BODY()
	
	UGPHealthComponentCaravan();
public:		
	
	UPROPERTY()
	FCaravanDestroy CaravanDeathDelegate;
	UPROPERTY()
	FCaravanUpdateHealth UpdateHealthDelegate;	

	UPROPERTY()
	AActor* MyOwner = nullptr;


	UFUNCTION(BlueprintCallable)
	float GetCurrentHealth() { return currentHealth; }	

	void SetHealth(float Health) { currentHealth = Health;}

	UFUNCTION(BlueprintCallable)
	float GetMaxHealth() { return maxHealth; }
	UFUNCTION(BlueprintCallable)
	void SetMaxHealth(float AddMaxToCurrentHp) { maxHealth = AddMaxToCurrentHp; }

	UFUNCTION(BlueprintCallable)
	float GetHealthPercent() { return (currentHealth / maxHealth) * 100;}
	
	UFUNCTION(BlueprintCallable)
	float PercentDamageIncrease() { return (currentHealth / maxHealth - 1) * -1 ;}
	

	UPROPERTY(BlueprintReadOnly)
	bool bHealthSet = false;

	UPROPERTY()
	bool bDead = false;

protected:
	
	virtual void BeginPlay() override;	
	
	UFUNCTION()
	void TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* EventInstigator, AActor* DamageCauser);
	
	UFUNCTION()
	void OnDeath() const;
	
	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* HealthWidgetComp;

private:	
	float currentHealth = 999.f;
	float maxHealth = 1000.f;
	
	
};