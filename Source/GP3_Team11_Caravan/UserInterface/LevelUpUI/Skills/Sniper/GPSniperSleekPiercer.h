#pragma once
#include "GP3_Team11_Caravan/UserInterface/LevelUpUI/Skills/GPTreeSkill.h"
#include "GPSniperSleekPiercer.generated.h"

UCLASS()
class UGPSniperSleekPiercer : public UGPTreeSkill
{
	GENERATED_BODY()
public:
	virtual void ApplySkill(UGPGameInstance* GI) override;
};
