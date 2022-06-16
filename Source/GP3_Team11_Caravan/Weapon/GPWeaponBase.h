#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GPWeaponBase.generated.h"

class USphereComponent;
class UNiagaraComponent;
class UNiagaraSystem;

UCLASS()
class GP3_TEAM11_CARAVAN_API AGPWeaponBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGPWeaponBase();

	UFUNCTION(BlueprintCallable)
	void Attack(AActor* target);
	
	void DrawBulletTrace(UNiagaraComponent* bullet, FVector target, float accuracyModifier, bool bHit);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	USceneComponent* Root;
	// Bullet trace spawn
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* Muzzle;
	UPROPERTY(VisibleAnywhere)
	USphereComponent* RangedArea;

	// Bullet trace
	UPROPERTY(EditAnywhere)
	UNiagaraSystem* BulletTraceSystem;
	
	// Shoot effect
	UPROPERTY(EditAnywhere)
	UNiagaraSystem* ShootEffect;

	// Can't walk and shoot
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bWalkAndShoot = false;
	FVector PreviousPosition = FVector::Zero();

	// Timer between shoots
	float CooldownTimer = 0;
	float reloadTimer = 0;

	// Counts bullets, compared with bullet/mag to know when to reload
	UPROPERTY(BlueprintReadWrite)
	int BulletsShot = 0;

	// ##########################
	// ######### Events #########

	UFUNCTION(BlueprintImplementableEvent)
	void FiredShot();

	UFUNCTION(BlueprintImplementableEvent)
	void Reloading();

	bool bReloading = false;
	
	// ###################################
	// ######### Bullet specific #########
	/*Base damage per bullet*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullets")
	float Damage = 1;

	/*Amount of bullets per shot*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullets")
	int AmountOfBullets = 1;

	/*Bullets per S, 60 = 1 per minute*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullets")
	float RPS = 0.5;


	
	// ###################################
	// ######### Reload specific #########
	/*How many bullets before reloading*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reloading")
	int BulletsPerMag = 30;

	/*Write Seconds*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reloading")
	int ReloadTime = 2;


	
	// #####################################
	// ######### Accuracy specific #########
	/*Effective range, outside of this weapon always miss*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accuracy")
	float Range = 500;

	/*Modifies accuracy depending on distance, percentage*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accuracy")
	int AccuracyOverDistance = 50;
	
	/*Write percentage, This is inside effective range*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Accuracy")
	float Accuracy = 90;


	
	// #########################################
	// ######### Critical hit specific #########
	/*Applies to every bullet, Write percentage*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Critical Strike")
	int CriticalStrikeChance = 20;
	
	/*Amount multiplied by damage on critical hit*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Critical Strike")
	float CriticalStrikeMultiplier = 5;
	


	// ###############################
	// ######### Debug stuff #########
	DECLARE_DELEGATE_OneParam(AttackDelegate, AActor*);
	UPROPERTY(EditInstanceOnly, Category = "Debug")
	bool EnableDebug = false;
	/*Target to shoot*/
	UPROPERTY(EditInstanceOnly, Category = "Debug")
	AActor* DebugTarget;
};