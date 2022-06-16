#include "EnemyAI.h"
#include "EnemyAIController.h"
#include "AITypes.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"



AEnemyAI::AEnemyAI()
{
	PrimaryActorTick.bCanEverTick = true;


  PlayerCollisionDetection = CreateDefaultSubobject<USphereComponent>(TEXT("Player Collision Detection"));

  PlayerCollisionDetection->SetupAttachment(RootComponent);

  PlayerAttackCollisionDetection = CreateDefaultSubobject<USphereComponent>(TEXT("Player Attack Collision Detection"));
	
  PlayerAttackCollisionDetection->SetupAttachment(RootComponent);

  PlayerCollisionDetection->OnComponentBeginOverlap.AddDynamic(this, &AEnemyAI::OnPlayerDetectedOverlapBegin);

  PlayerCollisionDetection->OnComponentEndOverlap.AddDynamic(this, &AEnemyAI::OnPlayerDetectedOverlapEnd);

  PlayerAttackCollisionDetection->OnComponentBeginOverlap.AddDynamic(this, &AEnemyAI::OnPlayerAttackOverlapBegin);

  PlayerAttackCollisionDetection->OnComponentEndOverlap.AddDynamic(this, &AEnemyAI::OnPlayerAttackOverlapEnd);
	 
	  
	  

}

void AEnemyAI::MoveToPlayer()
{
	//EnemyAIController -> MoveToLocation(PlayerREF->GetActorLocation(), StoppingDistance, true);
}

void AEnemyAI::SeekPlayer()
{
	MoveToPlayer();
	GetWorld()->GetTimerManager().SetTimer(SeekPlayerTimerHandle, this, &AEnemyAI::SeekPlayer, 0.25f, true);
	
}

void AEnemyAI::StopSeekingPlayer()
{
	GetWorld()->GetTimerManager().ClearTimer(SeekPlayerTimerHandle);
}

void AEnemyAI::OnPlayerDetectedOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)		
{
	//PlayerREF = Cast</*Player Class here*/>(OtherActor);

	//if (PlayerREF)
	//{
	//	playerDetected = true;
	//	SeekPlayer();
	//}
}

void AEnemyAI::OnPlayerDetectedOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//PlayerREF = Cast</*Player Class here*/>(OtherActor);

	//if (PlayerREF)
	//{
	//	playerDetected = false;
	//	StopSeekingPlayer();
	//	
	//}
}

void AEnemyAI::OnPlayerAttackOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//PlayerREF = Cast</*Player Class here*/>(OtherActor);

	//if (PlayerREF)
	//{
	//	canAttackPlayer = true;

	//	AttackPlayer();
	//}
}

void AEnemyAI::OnPlayerAttackOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//PlayerREF = Cast</*Player Class here*/>(OtherActor);

	//if (PlayerREF)
	//{
	//	canAttackPlayer = false;

	//	SeekPlayer();
	//}
}

void AEnemyAI::AttackPlayer() 
{

}
	  