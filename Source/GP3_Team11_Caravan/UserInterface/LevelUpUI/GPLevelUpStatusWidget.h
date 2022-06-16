#pragma once
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "GPLevelUpStatusWidget.generated.h"

class UGPGameInstance;
class UGPPlayerUnitStats;
class UGPSkillTreeAssetData;
class UTextBlock;
class UButton;

UCLASS()
class UGPLevelUpStatusWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	void SetHealthModifierTextWidget();
	void SetDamageModifierTextWidget();
	void SetSpeedModifierTextWidget();

	UFUNCTION()
	void OnSkillOnePressed();
	UFUNCTION()
	void OnSkillTwoPressed();
	UFUNCTION()
	void OnSkillThreePressed();
	UFUNCTION()
	void OnSkillFourPressed();
	UFUNCTION()
	void OnSkillFivePressed();
	UFUNCTION()
	void OnSkillSixPressed();

	UFUNCTION(BlueprintImplementableEvent)
	UTextBlock* GetNameTextWidget();
	UFUNCTION(BlueprintImplementableEvent)
	UTextBlock* GetTitleTextWidget();
	UFUNCTION(BlueprintImplementableEvent)
	UTextBlock* GetPointsWarningTextWidget();
	UFUNCTION(BlueprintImplementableEvent)
	UImage* GetHeaderIconImage();
	UFUNCTION(BlueprintImplementableEvent)
	UImage* GetHeaderBorderImage();
	
	UFUNCTION(BlueprintImplementableEvent)
	UTextBlock* GetHealthModifierTextWidget();
	UFUNCTION(BlueprintImplementableEvent)
	UTextBlock* GetDamageModifierTextWidget();
	UFUNCTION(BlueprintImplementableEvent)
	UTextBlock* GetSpeedModifierTextWidget();
	UFUNCTION(BlueprintImplementableEvent)
	UTextBlock* GetPointsTextWidget();
	UFUNCTION(BlueprintImplementableEvent)
	TArray<UButton*> GetSkillsButtons();
	UFUNCTION(BlueprintImplementableEvent)
	TArray<UImage*> GetLockImages();
	
	int Index;

	UPROPERTY(BlueprintReadWrite)
	bool bUpdateUI = false;
	UPROPERTY(EditAnywhere)
	FColor DisabledTint;
	UPROPERTY()
	UGPSkillTreeAssetData* SkillTree;
	UPROPERTY()
	UGPGameInstance* GameInstance;

private:
	void InitHeader();
	void InitSkillClickEvents();
	void InitSkills(int level);
		
	void LockTree(TArray<int> activeSkills);
	void UnlockSkill(int skillIndex, bool applySkill);
	void UnlockSkillTree(int level);
	void DisableSkillTree(int level);
};
