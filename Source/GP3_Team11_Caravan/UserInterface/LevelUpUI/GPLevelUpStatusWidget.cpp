#include "GPLevelUpStatusWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Skills/GPSkillTreeAssetData.h"
#include "Skills/GPTreeSkill.h"
#include "Kismet/GameplayStatics.h"
#include "GP3_Team11_Caravan/GPGameInstance.h"

void UGPLevelUpStatusWidget::NativeConstruct()
{
	Super::NativeConstruct();
	GameInstance = GetWorld()->GetGameInstance<UGPGameInstance>();
	
	InitSkillClickEvents();
	InitSkills(GameInstance->SkillTreeStats[Index].Level); // 1-3
	InitHeader();
	
	LockTree(GameInstance->SkillTreeStats[Index].UnlockedSkills);
	
	GameInstance->SkillTreeStats[Index].Points++;
	bUpdateUI = true;
}

void UGPLevelUpStatusWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if(bUpdateUI)
	{
		GetPointsTextWidget()->SetText(FText::FromString(FString::Printf(TEXT("Points: %d"),
			GameInstance->SkillTreeStats[Index].Points)));

		if(GameInstance->SkillTreeStats[Index].Points > 0)
		{
			GetPointsWarningTextWidget()->SetVisibility(ESlateVisibility::Visible);
		}
		else GetPointsWarningTextWidget()->SetVisibility(ESlateVisibility::Hidden);
		
		bUpdateUI = false;	
	}
}

void UGPLevelUpStatusWidget::LockTree(TArray<int> activeSkills)
{
	for (int skillIndex : activeSkills)
	{
		UnlockSkill(skillIndex, false);
	}
}

void UGPLevelUpStatusWidget::InitHeader()
{
	GetNameTextWidget()->SetText(FText::FromName(SkillTree->UnitName));
	GetTitleTextWidget()->SetText(FText::FromName(SkillTree->UnitTitle));
	GetHeaderBorderImage()->SetColorAndOpacity(FLinearColor(FColor::FromHex(SkillTree->UnitBorderColorHex)));
	GetHeaderIconImage()->SetBrushResourceObject(SkillTree->UnitIcon);

	GetHeaderIconImage()->Brush.ImageSize = FVector2D(SkillTree->UnitIcon->GetImportedSize().X/2,
		SkillTree->UnitIcon->GetImportedSize().Y/2);
}

void UGPLevelUpStatusWidget::InitSkillClickEvents()
{
	GetSkillsButtons()[0]->OnClicked.AddDynamic(this, &UGPLevelUpStatusWidget::OnSkillOnePressed);
	GetSkillsButtons()[1]->OnClicked.AddDynamic(this, &UGPLevelUpStatusWidget::OnSkillTwoPressed);
	GetSkillsButtons()[2]->OnClicked.AddDynamic(this, &UGPLevelUpStatusWidget::OnSkillThreePressed);
	GetSkillsButtons()[3]->OnClicked.AddDynamic(this, &UGPLevelUpStatusWidget::OnSkillFourPressed);
	GetSkillsButtons()[4]->OnClicked.AddDynamic(this, &UGPLevelUpStatusWidget::OnSkillFivePressed);
	GetSkillsButtons()[5]->OnClicked.AddDynamic(this, &UGPLevelUpStatusWidget::OnSkillSixPressed);
}

void UGPLevelUpStatusWidget::InitSkills(int level)
{
	//Initialize every skill from the data asset
	for(int i = 0; i < GetSkillsButtons().Num(); i++)
	{
		GetSkillsButtons()[i]->WidgetStyle.Normal.SetResourceObject(SkillTree->Skills[i].Icon);
		GetSkillsButtons()[i]->WidgetStyle.Hovered.SetResourceObject(SkillTree->Skills[i].Icon);
		GetSkillsButtons()[i]->WidgetStyle.Pressed.SetResourceObject(SkillTree->Skills[i].Icon);
	}

	UnlockSkillTree(level);
	DisableSkillTree(level);
}

/*void UGPLevelUpStatusWidget::SetHealthModifierTextWidget()
{
	int modifier = PlayerUnitStatsComp->GetHealthModifier() * 100;
	GetHealthModifierTextWidget()->SetText(FText::FromString(FString::Printf(TEXT("Health: %d"), modifier)));
}

void UGPLevelUpStatusWidget::SetDamageModifierTextWidget()
{
	int modifier = PlayerUnitStatsComp->GetDamageModifier() * 100;
	GetDamageModifierTextWidget()->SetText(FText::FromString(FString::Printf(TEXT("Damage: %d"), modifier)));
}

void UGPLevelUpStatusWidget::SetSpeedModifierTextWidget()
{
	int modifier = PlayerUnitStatsComp->GetSpeedModifier() * 100;
	GetSpeedModifierTextWidget()->SetText(FText::FromString(FString::Printf(TEXT("Speed: %d"), modifier)));
}*/

void UGPLevelUpStatusWidget::OnSkillOnePressed()
{
	if(GameInstance->SkillTreeStats[Index].Points > 0)
		UnlockSkill(0, true);
}

void UGPLevelUpStatusWidget::OnSkillTwoPressed()
{
	if(GameInstance->SkillTreeStats[Index].Points > 0)
		UnlockSkill(1, true);
}

void UGPLevelUpStatusWidget::OnSkillThreePressed()
{
	if(GameInstance->SkillTreeStats[Index].Points > 0)
		UnlockSkill(2, true);
}

void UGPLevelUpStatusWidget::OnSkillFourPressed()
{
	if(GameInstance->SkillTreeStats[Index].Points > 0)
		UnlockSkill(3, true);
}

void UGPLevelUpStatusWidget::OnSkillFivePressed()
{
	if(GameInstance->SkillTreeStats[Index].Points > 0)
		UnlockSkill(4, true);
}

void UGPLevelUpStatusWidget::OnSkillSixPressed()
{
	if(GameInstance->SkillTreeStats[Index].Points > 0)
		UnlockSkill(5, true);
}

void UGPLevelUpStatusWidget::UnlockSkill(int skillIndex, bool applySkill)
{
	if(applySkill && GameInstance->SkillTreeStats[Index].Points >= 1)
	{
		SkillTree->Skills[skillIndex].Class.GetDefaultObject()->ApplySkill(GameInstance);
		GameInstance->SkillTreeStats[Index].UnlockedSkills.Add(skillIndex);
		GameInstance->SkillTreeStats[Index].Points--;
		GameInstance->SkillTreeStats[Index].Level++;
	}

	GetSkillsButtons()[skillIndex]->WidgetStyle.Normal.TintColor = FSlateColor(DisabledTint);
	
	const int level = GameInstance->SkillTreeStats[Index].Level;

	UnlockSkillTree(level);
	DisableSkillTree(level);

	bUpdateUI = true;
}

void UGPLevelUpStatusWidget::UnlockSkillTree(int level)
{	
	for(int i = 0; i < GetSkillsButtons().Num(); i++)
	{
		if(i < (level * 2))
		{
		    GetSkillsButtons()[i]->SetIsEnabled(true);
		    continue;
		}

		GetSkillsButtons()[i]->SetIsEnabled(false);
	}

	for(int i = 0; i < GetLockImages().Num(); i++)
	{
		if(i < level)
		{
			GetLockImages()[i]->SetVisibility(ESlateVisibility::Hidden);
			continue;
		}
		
		GetLockImages()[i]->SetVisibility(ESlateVisibility::Visible);
	}
}

void UGPLevelUpStatusWidget::DisableSkillTree(int level)
{
	for(int i = 0; i < (level - 1) * 2; i++)
	{
		GetSkillsButtons()[i]->SetIsEnabled(false);
	}
}

