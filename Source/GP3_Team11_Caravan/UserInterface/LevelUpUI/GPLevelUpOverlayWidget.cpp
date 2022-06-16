#include "GPLevelUpOverlayWidget.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/HorizontalBox.h"
#include "Components/Button.h"
#include "GPLevelUpStatusWidget.h"
#include "GP3_Team11_Caravan/GPGameInstance.h"

void UGPLevelUpOverlayWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GetPointsButton()->OnClicked.AddDynamic(this, &UGPLevelUpOverlayWidget::OnPointsButtonClicked);

	for (int i = 0; i < UnitCount; i++)
	{
		AddUnitStatus(i);
	}
}

void UGPLevelUpOverlayWidget::AddUnitStatus(int index)
{
	UGPLevelUpStatusWidget* unitStatus = NewObject<UGPLevelUpStatusWidget>(this, UnitWidgetClass);
	unitStatus->Index = index;
	unitStatus->SkillTree = TreeDataAssets[index];
	unitStatus->SetPadding(FMargin(8, 30, 8, 0));

	LevelUpStatuses.Add(unitStatus);
	GetMainHorizontalBox()->AddChildToHorizontalBox(unitStatus);
}

void UGPLevelUpOverlayWidget::OnPointsButtonClicked()
{
	for (auto statWidget : LevelUpStatuses)
	{
		statWidget->GameInstance->SkillTreeStats[statWidget->Index].Points++;
		statWidget->bUpdateUI = true;
	}
}
