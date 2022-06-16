#pragma once

#include "CoreMinimal.h"
#include "GP_CaravanWinCondition.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class GP3_TEAM11_CARAVAN_API UGP_CaravanWinCondition : public UActorComponent
{
 GENERATED_BODY()

 UGP_CaravanWinCondition();
 
protected:
 virtual void BeginPlay() override;
 
public:
 virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

 UPROPERTY(EditAnywhere)
 FName NextLevel;
 
 float WinTimer = 0;

 UPROPERTY(EditAnywhere)
 float WaitTime = 5;

 FVector LastPosition;
};
