#include "GPAbilitySystem.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Components/ActorComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GP3_Team11_Caravan/GPComponents/GPHealthComponent.h"

#include "Kismet/GameplayStatics.h"

// Unreals functions
UGPAbilitySystem::UGPAbilitySystem()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UGPAbilitySystem::BeginPlay()
{
	Super::BeginPlay();
}

void UGPAbilitySystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if(CoolDownTimer > 0)
	{
		CoolDownTimer -= DeltaTime;
	}
}




/**
 * @brief 
 * @param scale will affect all activated floats
 * @param targets = actors effected by an action ability
 * @param particleSpawnLocation = location of particle system spawn
 */
bool UGPAbilitySystem::ActivateAbility(float scale, TArray<AActor*> targets, FVector particleSpawnLocation)
{
	if(CoolDownTimer > 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red,
				FString::Printf(TEXT("Cooldown: %f sec"), CoolDownTimer));
		return false;
	}
	
	
	// ##############################
	// ######### Stat Bonus #########
	// Health
	if(bAffectHealth)
	{
		if (targets.IsEmpty())
		{
			UE_LOG(LogTemp, Warning, TEXT("Targets are empty"));
			return false;
		} 

		// Gets Health component in target
		TArray<UGPHealthComponent*> healthComp;
		targets[0]->GetComponents<UGPHealthComponent>(healthComp);

		// Checks that array isn't empty
		if(healthComp.Num() == 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("No Health component in owner of ability component"));
			return false;
		}

		// Apply effect if array position isn't null
		if(healthComp[0] != nullptr)
		{
			healthComp[0]->SetCurrentHealth(HealthBonus * scale);
		}
		
		CoolDownTimer = Cooldown * 60;
	}
	// Movement speed
	if(bAffectSpeed)
	{
		// Gets Movement component in target
		TArray<UCharacterMovementComponent*> moveComp;
		targets[0]->GetComponents<UCharacterMovementComponent>(moveComp);

		// Checks that array isn't empty
		if(moveComp.Num() == 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("No Movement component in owner of ability component"));
			return false;
		}

		// Apply effect if array position isn't null
		if(moveComp[0] != nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red,
					FString::Printf(TEXT("Old speed: %f, New speed: %f"),
						moveComp[0]->MaxWalkSpeed,
						moveComp[0]->MaxWalkSpeed * ((SpeedBonus * scale) * 0.01 + 1)));
			moveComp[0]->MaxWalkSpeed = moveComp[0]->MaxWalkSpeed * ((SpeedBonus * scale) * 0.01 + 1);
		}
		
		CoolDownTimer = Cooldown * 60;
	}


	
	// ##################################
	// ######### Action Ability #########
	if(bActionAbility)
	{
		// Attack if inside Range + Effect area
		for(int i = 0; i < targets.Num(); i++)
		{
			if(FVector::Distance(targets[i]->GetActorLocation(), GetOwner()->GetActorLocation()) < Range + EffectArea)
			{
				GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Emerald,
						TEXT("Attacked"));
				UGameplayStatics::ApplyDamage(targets[i], Damage * scale,
				GetWorld()->GetFirstPlayerController(), GetOwner(), UDamageType::StaticClass());
			}
		}
		CoolDownTimer = Cooldown * 60;
	}

	// Play Niagara particle system
	UNiagaraComponent* ParticleEffect = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetOwner(), PlayedEffectSystem,
			particleSpawnLocation, FRotator(0), FVector(1.f), true, false);
	ParticleEffect->Activate();

	return true;
}


