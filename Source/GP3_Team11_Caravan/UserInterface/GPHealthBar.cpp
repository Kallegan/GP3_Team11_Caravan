#include "GPHealthBar.h"
#include "GP3_Team11_Caravan/GPComponents/GPHealthComponent.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"


void UGPHealthBar::UpdateHealthBar() const
{
	if(OwnerEnemy.IsValid())
		HealthBar->SetPercent(OwnerEnemy->HealthComponent->GetCurrentHealth() / OwnerEnemy->HealthComponent->GetMaxHealth());
	else if(OwnerPlayer.IsValid())
	{
		HealthBar->SetPercent(OwnerPlayer->HealthComponent->GetCurrentHealth() / OwnerPlayer->HealthComponent->GetMaxHealth());
	}		
}

void UGPHealthBar::UpdateCoverIconNoCover() const
{
	CoverImage->SetOpacity(0.20f);	
}

void UGPHealthBar::UpdateCoverIconFullCover() const
{
	CoverImage->SetOpacity(1.f);	
}

void UGPHealthBar::UpdateCoverIconHalfCover() const
{
	CoverImage->SetOpacity(1.f);
	
}

