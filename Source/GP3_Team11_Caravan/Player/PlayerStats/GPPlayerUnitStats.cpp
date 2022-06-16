#include "GPPlayerUnitStats.h"
#include "GP3_Team11_Caravan/Player/PlayerStats/GPPlayerUnitStats.h"

float UGPPlayerUnitStats::GetSpeedModifier()
{
	return speedModifier;
}

float UGPPlayerUnitStats::GetHealthModifier()
{
	return healthModifier;
}

float UGPPlayerUnitStats::GetDamageModifier()
{
	return damageModifier;
}

void UGPPlayerUnitStats::SetSpeedModifier(float value)
{
	speedModifier = value;
}

void UGPPlayerUnitStats::SetHealthModifier(float value)
{
	healthModifier = value;
}

void UGPPlayerUnitStats::SetDamageModifier(float value)
{
	damageModifier = value;
}
