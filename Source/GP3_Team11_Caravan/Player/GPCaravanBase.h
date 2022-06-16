#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GPCaravanBase.generated.h"

class UGPHealthComponentCaravan;
class UWidgetComponent;
class UGPHealthBar;
class UGPGameInstance;


UCLASS()
class GP3_TEAM11_CARAVAN_API AGPCaravanBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGPCaravanBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UGPHealthComponentCaravan* CaravanHealthComponent;

	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* HealthWidgetComp;


	UFUNCTION()
	virtual void CaravanOnDeath(AActor* OwningActor);

	UFUNCTION()
	virtual void CaravanUpdateHealth(AActor* OwningActor);


	UFUNCTION(BlueprintImplementableEvent)
	void CaravanDamageEvent();

	UFUNCTION(BlueprintImplementableEvent)
	void CaravanDeathEvent();
	

private:

	UPROPERTY()
	UGPGameInstance* GameInstance = nullptr;

	float currentHealth = 0;
	float maxHealth = 0;
	

};
