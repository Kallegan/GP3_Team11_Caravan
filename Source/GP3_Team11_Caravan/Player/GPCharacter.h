#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GP3_Team11_Caravan/Enemy/GPEnemyBase.h"
#include "GPCharacter.generated.h"

class AGPWeaponBase;
class UGPHealthComponent;
class UWidgetComponent;
class UGPHealthBar;
class UGPGameInstance;

UCLASS()
class GP3_TEAM11_CARAVAN_API AGPCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AGPCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UGPHealthComponent* HealthComponent;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UWidgetComponent* HealthWidgetComp;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnDeath(AActor* OwningActor);

	UFUNCTION()
	virtual void UpdateHealthBar(AActor* OwningActor);

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	


public:		
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnDeathBPEvent();

	UFUNCTION(BlueprintImplementableEvent)
	void UnitDamaged(float HealthPercent);
	
	
	UPROPERTY(BlueprintReadWrite)
	AActor* Target;

private:
	UPROPERTY()
	UGPHealthBar* HealthBar = nullptr;

	UPROPERTY()
	UGPGameInstance* GameInstance = nullptr;
	
	void updateEnemyPositions();	
	bool outOfSight() const;	
	bool behindCover(AActor* enemyActor) const;
	void setCover() const;
	float coverUpdate = 0.3f;
	
	UPROPERTY()
	TArray<FVector> EnemyPositions;	
};
