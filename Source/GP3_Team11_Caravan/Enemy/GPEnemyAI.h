#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GPEnemyAI.Generated.h"

UCLASS()
class GP3_TEAM11_CARAVAN_API AGPEnemyAI : public ACharacter
{
	GENERATED_BODY()


	
public:


	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	AGPEnemyAI();

	bool playerDetected;
	bool canAttackPlayer;

	/*class (PlayerClassGoesHere)* PlayerREF;*/

	UPROPERTY(EditAnywhere)
		class USphereComponent* PlayerCollisionDetection;

	UPROPERTY(EditAnywhere)
		class USphereComponent* PlayerAttackCollisionDetection;

	UPROPERTY(EditAnywhere)
		float StoppingDistance = 100.f;

	FTimerHandle SeekPlayerTimerHandle;

	FTimerHandle AttackPlayerTimerHandle;

	UFUNCTION()
		void MoveToPlayer();

	UFUNCTION()
		void SeekPlayer();

	UFUNCTION()
		void StopSeekingPlayer();

	UFUNCTION()
		void AttackPlayer();

	UFUNCTION()
		void StopAttackingPlayer();

	UFUNCTION()
		void WeaponAttack();

	UFUNCTION()
		void OnPlayerDetectedOverlapBegin(class UPrimitiveComponent* OverlappedComp,
			class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnPlayerDetectedOverlapEnd(class UPrimitiveComponent* OverlappedComp,
			class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);


	UFUNCTION()
		void OnPlayerAttackOverlapBegin(class UPrimitiveComponent* OverlappedComp,
			class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnPlayerAttackOverlapEnd(class UPrimitiveComponent* OverlappedComp,
			class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);

};