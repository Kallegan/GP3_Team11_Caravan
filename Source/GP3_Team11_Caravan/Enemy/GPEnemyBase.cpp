#include "GPEnemyBase.h"
#include "GP3_Team11_Caravan/UserInterface/GPHealthBar.h"
#include "GP3_Team11_Caravan/GPComponents/GPHealthComponent.h"
#include "Components/WidgetComponent.h"
#include "GP3_Team11_Caravan/GPGameInstance.h"

// Sets default values
AGPEnemyBase::AGPEnemyBase()
{
	PrimaryActorTick.bCanEverTick = true;	

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));	
	CapsuleComp->SetCapsuleSize(42.f,96.f);
	CapsuleComp->SetupAttachment(RootComponent);	
	
	HealthComponent = CreateDefaultSubobject<UGPHealthComponent>(TEXT("HealthComponent"));
	HealthComponent->OnDeathEvent.AddDynamic(this, &ThisClass::OnDeath);
	HealthComponent->UpdateHealthBar.AddDynamic(this, &ThisClass::UpdateHealthBar);	

	HealthWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
	HealthWidgetComp->AttachToComponent(CapsuleComp, FAttachmentTransformRules::KeepRelativeTransform);
	HealthWidgetComp->SetWidgetSpace(EWidgetSpace::Screen);
	HealthWidgetComp->SetDrawAtDesiredSize(true);

	
}


// Called when the game starts or when spawned
void AGPEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	HealthBar = Cast <UGPHealthBar>(HealthWidgetComp->GetUserWidgetObject());
	HealthBar->SetOwnerEnemy(this);

	GameInstance = GetWorld()->GetGameInstance<UGPGameInstance>();

	if(GameInstance)
	GameInstance->EnemyUnits.Add(this);	
	
}

void AGPEnemyBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if(GameInstance)
	GameInstance->EnemyUnits.Remove(this);	
}

// Called every frame
void AGPEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	coverUpdate -= DeltaTime;

	
	if(coverUpdate <= 0.0f)
	{
		updateEnemyPositions();

		if(outOfSight())
			setCover();
		else
			HealthBar->UpdateCoverIconNoCover();	
		
		coverUpdate = 2.f;	
	}
}


void AGPEnemyBase::OnDeath(AActor*)
{	
	OnDeathBPEvent();	
}

void AGPEnemyBase::UpdateHealthBar(AActor*)
{
	HealthBar->UpdateHealthBar();	
}


//cover temp

void AGPEnemyBase::updateEnemyPositions()
{
	PlayerPositions.Empty();
	
	for (int i = 0; i < GameInstance->PlayerUnits.Num(); i++)	
		PlayerPositions.Add(GameInstance->PlayerUnits[i]->GetActorLocation());
}

bool AGPEnemyBase::outOfSight() const
{
	for (int i = 0; i < PlayerPositions.Num(); i++)
	{			
		{
			if(GetDistanceTo(GameInstance->PlayerUnits[i]) < 1500)
			{		
				if(behindCover(GameInstance->PlayerUnits[i]))
				{
					continue;
				}
				
				return false;				
			}		
		}
	}
	
	return true;
}

bool AGPEnemyBase::behindCover(AActor* enemyActor) const
{
	FHitResult HitResult = FHitResult();
	FVector OwnerLocation = GetActorLocation();
	OwnerLocation = OwnerLocation -= FVector(0,0,80);
	
	FVector EnemyLocation = enemyActor->GetActorLocation();
	FVector NormalizedDir = EnemyLocation-OwnerLocation;
	NormalizedDir.Normalize();
	
	FCollisionQueryParams Params = FCollisionQueryParams::DefaultQueryParam;	
	
	
	if(GetWorld()->LineTraceSingleByChannel(HitResult, OwnerLocation, (NormalizedDir*300)+OwnerLocation, ECC_Visibility, Params))
	{
		if (HitResult.GetActor()->ActorHasTag("FullCover") || (HitResult.GetActor()->ActorHasTag("HalfCover")))
		{			
			return true;
		}
	}
	
	return false;
}

void AGPEnemyBase::setCover() const
{
	int fullCover = 0;
	int halfCover = 0;
	int noCover = 0;
	
	for (auto enemy : GameInstance->PlayerUnits)
	{
		FHitResult HitResult = FHitResult();
		FVector OwnerLocation = GetActorLocation();
		OwnerLocation = OwnerLocation -= FVector(0,0,80);
	
		FVector EnemyLocation = enemy->GetActorLocation();
		FVector NormalizedDir = EnemyLocation-OwnerLocation;
		NormalizedDir.Normalize();		
	
		FCollisionQueryParams Params = FCollisionQueryParams::DefaultQueryParam;
		Params.AddIgnoredActor(this);		
	
		if(GetWorld()->LineTraceSingleByChannel(HitResult, OwnerLocation, (NormalizedDir*300)+OwnerLocation, ECC_Visibility, Params))
		{

			if (HitResult.GetActor()->ActorHasTag("FullCover"))
			{
				fullCover++;
			}			
			else if(HitResult.GetActor()->ActorHasTag("HalfCover"))
			{			
				halfCover++;
			}
			else
			{
				noCover++;
			}		
		}		
	}

	if(noCover >= fullCover+halfCover)
	{
		HealthBar->UpdateCoverIconNoCover();
	}
	else if(fullCover > halfCover)
	{
		HealthBar->UpdateCoverIconFullCover();
	}
	else
	{
		HealthBar->UpdateCoverIconHalfCover();
	}	
}