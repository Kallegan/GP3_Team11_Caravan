#pragma once
#include "GPSkillTreeAssetData.generated.h"

class UGPTreeSkill;

USTRUCT()
struct FSkill
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UGPTreeSkill> Class;
	UPROPERTY(EditAnywhere)
	FName Name;
	UPROPERTY(EditAnywhere)
	UTexture2D* Icon;
};

UCLASS()
class UGPSkillTreeAssetData : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	UTexture2D* UnitIcon;
	UPROPERTY(EditAnywhere)
	FName UnitName;
	UPROPERTY(EditAnywhere)
	FName UnitTitle;
	UPROPERTY(EditAnywhere)
	FString UnitBorderColorHex;

	UPROPERTY(EditAnywhere)
	TArray<FSkill> Skills;
};
