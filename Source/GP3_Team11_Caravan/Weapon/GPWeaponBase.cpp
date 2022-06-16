#include "GPWeaponBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

// Unreals functions
AGPWeaponBase::AGPWeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	Muzzle = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle"));
	Muzzle->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);

	RangedArea = CreateDefaultSubobject<USphereComponent>(TEXT("Range"));
	RangedArea->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	
	RootComponent = Root;
}

void AGPWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	RangedArea->SetSphereRadius(Range);
}

void AGPWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(CooldownTimer > 0) { CooldownTimer--; }
	if(reloadTimer > 0)
	{
		reloadTimer--;
		if( !bReloading )
		{
			Reloading();
			bReloading = true;
		}
	}
}

void AGPWeaponBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if(EnableDebug)
	{
		PlayerInputComponent->BindAction<AttackDelegate>("Shoot", IE_Pressed, this, &AGPWeaponBase::Attack, DebugTarget);
	}
}




/**
 * @brief 
 * @param target of the attack
 */
void AGPWeaponBase::Attack(AActor* target)
{
	// If close enough
	float dist = FVector::Distance(GetActorLocation(), target->GetActorLocation());
	if(dist > Range || target == nullptr)
	{
		if(EnableDebug)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green,
				FString::Printf(TEXT("To far away, Distance: %f"), dist));
		}
		return;
	}

	// If walking, no shoot
	if(!bWalkAndShoot)
	{
		if(PreviousPosition != GetActorLocation())
		{
			PreviousPosition = GetActorLocation();
			return;
		}
	}
	PreviousPosition = GetActorLocation();
	
	if(CooldownTimer > 0 || reloadTimer > 0) { return; }
	bReloading = false;
	// Shooting cooldown, Converts rounds per Seconds to rounds per Milliseconds
	CooldownTimer = RPS * 60;

	// Bullet shot and Reloading
	BulletsShot++;
	if(BulletsShot >= BulletsPerMag)
	{
		BulletsShot = 0;
		reloadTimer = ReloadTime * 60;

		if(EnableDebug)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Purple,
				TEXT("Reloading"));
		}
	}
	
	// Decrease accuracy with distance
	float accuracyModifier = 1 - (dist / Range);
	accuracyModifier = FMath::Clamp(accuracyModifier + (AccuracyOverDistance * 0.01f), 0, 1);
	
	if(EnableDebug)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue,
			FString::Printf(TEXT("Distance, mod: %f"), accuracyModifier));
	}
	
	// Creates a list with every bullet
	TArray<float> currentDamage;
	currentDamage.Init(0, AmountOfBullets);
	
	for (int i = 0; i < AmountOfBullets; i++)
	{
		// Bullets
		UNiagaraComponent* Bullet = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, BulletTraceSystem,
			Muzzle->GetComponentLocation(), FRotator(0), FVector(1.f), true, false);
		
		// If hit
		if(FMath::RandRange(1, 100) > Accuracy * accuracyModifier)
		{
			DrawBulletTrace(Bullet, target->GetActorLocation(), accuracyModifier, false);
			
			if(EnableDebug)
			{
				GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green,
					TEXT("Miss"));
			}
			continue;
		}

		
		DrawBulletTrace(Bullet, target->GetActorLocation(), accuracyModifier, true);
		
		currentDamage[i] = Damage; 
		if(FMath::RandRange(1, 100) < CriticalStrikeChance)
		{
			currentDamage[i] *= CriticalStrikeMultiplier;
		}
	}

	float damageSum = 0;
	for(auto& dmg : currentDamage)
	{
		damageSum += dmg;
	}

	FiredShot();

	

	// Sends damage to target actor
	UGameplayStatics::ApplyDamage(target, damageSum, GetWorld()->GetFirstPlayerController(), this, UDamageType::StaticClass());

	if(EnableDebug)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("Hit, Damage: %f"), damageSum));
	}
}

// Play all particle systems
void AGPWeaponBase::DrawBulletTrace(UNiagaraComponent* bullet, FVector target, float accuracyModifier, bool bHit)
{
	// Shoot smoke
	UNiagaraComponent* ShootSmoke = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ShootEffect,
		Muzzle->GetComponentLocation(), FRotator(0), FVector(1.f), true, false);
	
	FVector offset;
	float inverseAccuracy = 1 - accuracyModifier;
	float hitRange = 20 * inverseAccuracy;
	
	if(bHit)
	{
		// Hit
		offset.X = FMath::FRandRange(-hitRange,hitRange); 
		offset.Y = FMath::FRandRange(-hitRange,hitRange); 
		offset.Z = FMath::FRandRange(-hitRange + 40, hitRange + 40);
	}
	else
	{
		// Miss
		offset.X = FMath::FRandRange(-hitRange,hitRange); 
		offset.Y = FMath::FRandRange(-hitRange,hitRange); 
		offset.Z = FMath::FRandRange(-hitRange - 40, hitRange);
	}

	// Spawn bullet effect
	bullet->SetNiagaraVariableVec3(FString("TargetEnd"), target + offset);
	bullet->Activate();

	// Spawn shoot smoke
	ShootSmoke->SetWorldRotation(GetActorRotation());
	ShootSmoke->Activate();
}