#include "GPCaravanBase.h"
#include "GP3_Team11_Caravan/GPComponents/GPHealthComponentCaravan.h"
#include "GP3_Team11_Caravan/GPGameInstance.h"


// Sets default values
AGPCaravanBase::AGPCaravanBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;	

	CaravanHealthComponent = CreateDefaultSubobject<UGPHealthComponentCaravan>(TEXT("HealthComponent"));
	CaravanHealthComponent->CaravanDeathDelegate.AddDynamic(this, &ThisClass::CaravanOnDeath);
	CaravanHealthComponent->UpdateHealthDelegate.AddDynamic(this, &ThisClass::CaravanUpdateHealth);	
	
}

// Called when the game starts or when spawned
void AGPCaravanBase::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = GetWorld()->GetGameInstance<UGPGameInstance>();

	currentHealth = GameInstance->GetStartHealth();
	maxHealth = GameInstance->GetMaxHealth();

	CaravanHealthComponent->SetHealth(currentHealth);
	CaravanHealthComponent->SetMaxHealth(maxHealth);
	CaravanHealthComponent->bHealthSet = true;
	
	GameInstance->CaravanRef = this;
}


void AGPCaravanBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	
}

void AGPCaravanBase::CaravanOnDeath(AActor* OwningActor)
{	
	CaravanDeathEvent();
	GameInstance->SetStartHealth(GameInstance->GetMaxHealth());
}

void AGPCaravanBase::CaravanUpdateHealth(AActor* OwningActor)
{
	CaravanDamageEvent();
}

void AGPCaravanBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
	if(CaravanHealthComponent && !CaravanHealthComponent->bDead)
	GameInstance->SetStartHealth(CaravanHealthComponent->GetCurrentHealth());

	GameInstance->CaravanRef = nullptr;
}
