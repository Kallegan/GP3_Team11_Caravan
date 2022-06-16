#include "GP_CaravanWinCondition.h"

#include "Kismet/GameplayStatics.h"

UGP_CaravanWinCondition::UGP_CaravanWinCondition()
{
	PrimaryComponentTick.bCanEverTick = true;	
}


void UGP_CaravanWinCondition::BeginPlay()
{
	Super::BeginPlay();
	LastPosition = GetOwner()->GetActorLocation();
}

void UGP_CaravanWinCondition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if(FIntVector(LastPosition) ==  FIntVector(GetOwner()->GetActorLocation()))
	{
		WinTimer -= DeltaTime;
	}
	else
	{
		WinTimer = WaitTime;
	}

	if(WinTimer <= 0)
	{
		UGameplayStatics::OpenLevel(GetWorld(), NextLevel);
	}
	
	LastPosition = GetOwner()->GetActorLocation();
}
