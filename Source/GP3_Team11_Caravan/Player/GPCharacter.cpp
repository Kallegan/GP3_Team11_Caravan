#include "GPCharacter.h"
#include "GP3_Team11_Caravan/UserInterface/GPHealthBar.h"
#include "GP3_Team11_Caravan/GPComponents/GPHealthComponent.h"
#include "Components/WidgetComponent.h"
#include "Engine/RendererSettings.h"
#include "GP3_Team11_Caravan/GPGameInstance.h"

AGPCharacter::AGPCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UGPHealthComponent>(TEXT("HealthComponent"));
	HealthComponent->OnDeathEvent.AddDynamic(this, &ThisClass::OnDeath);
	HealthComponent->UpdateHealthBar.AddDynamic(this, &ThisClass::UpdateHealthBar);	
	
	HealthWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
	HealthWidgetComp->SetWidgetSpace(EWidgetSpace::Screen);
	HealthWidgetComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	HealthWidgetComp->SetDrawAtDesiredSize(true);	
}

void AGPCharacter::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = GetWorld()->GetGameInstance<UGPGameInstance>();

	Cast<UGPGameInstance>(GameInstance)->PlayerUnits.Add(this);	

	HealthBar = Cast <UGPHealthBar>(HealthWidgetComp->GetUserWidgetObject());
	HealthBar->SetOwnerPlayer(this);
	HealthBar->UpdateCoverIconNoCover();
}

void AGPCharacter::OnDeath(AActor* OwningActor)
{
	OnDeathBPEvent();
	HealthWidgetComp->ToggleVisibility();	
}

void AGPCharacter::UpdateHealthBar(AActor* OwningActor)
{
	HealthBar->UpdateHealthBar();
	
	UnitDamaged(HealthComponent->GetCurrentHealth() / HealthComponent->GetMaxHealth());
}

void AGPCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
	Cast<UGPGameInstance>(GameInstance)->PlayerUnits.Remove(this);		
}

void AGPCharacter::Tick(float DeltaTime)
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
		
		coverUpdate = 0.2f;	
	}
	
}



void AGPCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AGPCharacter::updateEnemyPositions()
{	
	EnemyPositions.Empty();
	
	for (int i = 0; i < GameInstance->EnemyUnits.Num(); i++)	
		EnemyPositions.Add(GameInstance->EnemyUnits[i]->GetActorLocation());	
}

bool AGPCharacter::outOfSight() const
{
	for (int i = 0; i < EnemyPositions.Num(); i++)
	{			
		{
			if(GetDistanceTo(GameInstance->EnemyUnits[i]) < 1500)
			{		
				if(behindCover(GameInstance->EnemyUnits[i]))
				{
					continue;
				}
				
				return false;				
			}		
		}
	}
	
	return true;
}


bool AGPCharacter::behindCover(AActor* enemyActor) const
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
		//DrawDebugLine(GetWorld(), OwnerLocation, (NormalizedDir*300)+OwnerLocation, FColor::Blue,true);

		if (HitResult.GetActor()->ActorHasTag("FullCover") || (HitResult.GetActor()->ActorHasTag("HalfCover")))
		{			
			return true;
		}
	}
	
	return false;
}

void AGPCharacter::setCover() const
{

	int fullCover = 0;
	int halfCover = 0;
	int noCover = 0;
	FHitResult HitResult = FHitResult();
	FVector OwnerLocation = GetActorLocation();
	OwnerLocation = OwnerLocation -= FVector(0,0,80);		

	FVector UnitForwardNormalized = GetActorForwardVector();
	UnitForwardNormalized.Normalize();
	
	FCollisionQueryParams Params = FCollisionQueryParams::DefaultQueryParam;
	Params.AddIgnoredActor(this);		
	
	
	
	for (auto enemy : GameInstance->EnemyUnits)
	{
		FVector EnemyLocation = enemy->GetActorLocation();
		FVector NormalizedDir = EnemyLocation-OwnerLocation;
		NormalizedDir.Normalize();		
		
		if(GetWorld()->LineTraceSingleByChannel(HitResult, OwnerLocation, (UnitForwardNormalized*300)+OwnerLocation, ECC_Visibility, Params))
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
