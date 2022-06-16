#pragma once
#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "GPEnemyBase.generated.h"

class UCapsuleComponent;
class UGPHealthComponent;
class UWidgetComponent;
class UGPHealthBar;
class UGPGameInstance;


UCLASS()
class GP3_TEAM11_CARAVAN_API AGPEnemyBase : public APawn
{
	GENERATED_BODY()
	
public:		
	AGPEnemyBase();	

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCapsuleComponent* CapsuleComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UGPHealthComponent* HealthComponent;
	
	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* HealthWidgetComp;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION()
	virtual void OnDeath(AActor* OwningActor);

	UFUNCTION()
	virtual void UpdateHealthBar(AActor* OwningActor);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnDeathBPEvent();
	
private:
	UPROPERTY()
	UGPHealthBar* HealthBar = nullptr;
	
	UPROPERTY()
	UGPGameInstance* GameInstance = nullptr;
	
	//cover temp
	void updateEnemyPositions();	
	bool outOfSight() const;	
	bool behindCover(AActor* enemyActor) const;
	void setCover() const;
	float coverUpdate = 0.3f;

	UPROPERTY()
	TArray<FVector> PlayerPositions;	
};