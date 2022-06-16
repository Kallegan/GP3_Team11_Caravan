#include "GPEnemyAI.h"
#include "GPEnemyAIController.h"
#include "AITypes.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"



AGPEnemyAI::AGPEnemyAI()
{
	PrimaryActorTick.bCanEverTick = true;


  PlayerCollisionDetection = CreateDefaultSubobject<USphereComponent>(TEXT("Player Collision Detection"));

  PlayerCollisionDetection->SetupAttachment(RootComponent);

  PlayerAttackCollisionDetection = CreateDefaultSubobject<USphereComponent>(TEXT("Player Attack Collision Detection"));
	
  PlayerAttackCollisionDetection->SetupAttachment(RootComponent);
  
	  

}

void AGPEnemyAI::BeginPlay() 
{
	Super::BeginPlay();

	PlayerCollisionDetection->OnComponentBeginOverlap.AddDynamic(this, &AGPEnemyAI::OnPlayerDetectedOverlapBegin);

	PlayerCollisionDetection->OnComponentEndOverlap.AddDynamic(this, &AGPEnemyAI::OnPlayerDetectedOverlapEnd);

	PlayerAttackCollisionDetection->OnComponentBeginOverlap.AddDynamic(this, &AGPEnemyAI::OnPlayerAttackOverlapBegin);

	PlayerAttackCollisionDetection->OnComponentEndOverlap.AddDynamic(this, &AGPEnemyAI::OnPlayerAttackOverlapEnd);
}


void AGPEnemyAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AGPEnemyAI::MoveToPlayer()
{
	//EnemyAIController -> MoveToLocation(PlayerREF->GetActorLocation(), StoppingDistance, true);
}

void AGPEnemyAI::SeekPlayer()
{
	MoveToPlayer();
	GetWorld()->GetTimerManager().SetTimer(SeekPlayerTimerHandle, this, &AGPEnemyAI::SeekPlayer, 0.25f, true);
	
}

void AGPEnemyAI::StopSeekingPlayer()
{
	GetWorld()->GetTimerManager().ClearTimer(SeekPlayerTimerHandle);

}

void AGPEnemyAI::OnPlayerDetectedOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)		
{
	//PlayerREF = Cast</*Player Class here*/>(OtherActor);

	//if (PlayerREF)
	//{
	//	playerDetected = true;
	//	SeekPlayer();
	//}
}

void AGPEnemyAI::OnPlayerDetectedOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//PlayerREF = Cast</*Player Class here*/>(OtherActor);

	//if (PlayerREF)
	//{
	//	playerDetected = false;
	//	StopSeekingPlayer();
	//	
	//}
}

void AGPEnemyAI::OnPlayerAttackOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//PlayerREF = Cast</*Player Class here*/>(OtherActor);

	//if (PlayerREF)
	//{
	//	canAttackPlayer = true;

	//	AttackPlayer();
	//}
}

void AGPEnemyAI::OnPlayerAttackOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//PlayerREF = Cast</*Player Class here*/>(OtherActor);

	//if (PlayerREF)
	//{
	//	canAttackPlayer = false;

	//   StopAttackingPlayer();

	//	SeekPlayer();
	//}


}

void AGPEnemyAI::AttackPlayer() 
{
	GetWorld()->GetTimerManager().SetTimer(AttackPlayerTimerHandle, this, &AGPEnemyAI::AttackPlayer, 0.25f, true);


	WeaponAttack();
}

void AGPEnemyAI::StopAttackingPlayer() 
{
	GetWorld()->GetTimerManager().ClearTimer(AttackPlayerTimerHandle);
}

	
void AGPEnemyAI::WeaponAttack() 
{
	//Weapon thingy goes here
}