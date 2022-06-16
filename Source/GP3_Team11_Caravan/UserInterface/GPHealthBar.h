#pragma once

#include "CoreMinimal.h"
#include "GP3_Team11_Caravan/Enemy/GPEnemyBase.h"
#include "Blueprint/UserWidget.h"

#include "GP3_Team11_Caravan/Player/GPCharacter.h"
#include "GPHealthBar.generated.h"

class UTextBlock;
class UProgressBar;
class UImage;

UCLASS(Abstract)
class GP3_TEAM11_CARAVAN_API UGPHealthBar : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetOwnerEnemy(AGPEnemyBase* InEnemy) { OwnerEnemy = InEnemy; }
	void SetOwnerPlayer(AGPCharacter* InCharacter) { OwnerPlayer = InCharacter; }

	void UpdateHealthBar() const;

	void UpdateCoverIconNoCover() const;
	
	void UpdateCoverIconFullCover() const;
	
	void UpdateCoverIconHalfCover() const;

	
protected:
	TWeakObjectPtr<AGPEnemyBase> OwnerEnemy = nullptr;
	TWeakObjectPtr<AGPCharacter> OwnerPlayer = nullptr;
	
	//makes it possible to bind from BP.
	UPROPERTY(meta=(BindWidget))
	UProgressBar* HealthBar;

	UPROPERTY(meta=(BindWidget))
	UImage* CoverImage;
};
