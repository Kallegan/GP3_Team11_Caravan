#include "GPHealthComponentCaravan.h"
#include "GP3_Team11_Caravan/UserInterface/GPHealthBar.h"


UGPHealthComponentCaravan::UGPHealthComponentCaravan()
{
	PrimaryComponentTick.bCanEverTick = false;	
}



void UGPHealthComponentCaravan::BeginPlay()
{
	Super::BeginPlay();

	MyOwner = GetOwner();		
	
	if(MyOwner)
	{
		MyOwner->OnTakeAnyDamage.AddDynamic(this, &UGPHealthComponentCaravan::TakeDamage);
		MyOwner->SetCanBeDamaged(true);
	}	
}

void UGPHealthComponentCaravan::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* EventInstigator, AActor* DamageCauser)
{
	if(Damage <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Damage <= 0"))
		return;	
	}

	currentHealth = FMath::Clamp(currentHealth - Damage, 0.f, maxHealth);
	UpdateHealthDelegate.Broadcast(MyOwner);	
			
	if(currentHealth <= 0 && !bDead && bHealthSet)
	{
		OnDeath();
		bDead = true;
	}		
}

void UGPHealthComponentCaravan::OnDeath() const
{
	if(MyOwner)
	{		
		CaravanDeathDelegate.Broadcast(MyOwner);
	}
}

