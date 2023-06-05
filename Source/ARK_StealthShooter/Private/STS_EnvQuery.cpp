// Fill out your copyright notice in the Description page of Project Settings.


#include "STS_EnvQuery.h"
#include <STS_HealingArea.h>
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"

USTS_EnvQuery::USTS_EnvQuery(const FObjectInitializer& ObjectInitializer)
{
	ValidItemType = UEnvQueryItemType_Actor::StaticClass();
}

void USTS_EnvQuery::RunTest(FEnvQueryInstance& QueryInstance) const
{
	for(FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
	{
		ASTS_HealingArea* HealingArea = Cast<ASTS_HealingArea>(GetItemActor(QueryInstance, It.GetIndex()));
		float Score = 0.0f;
		if(HealingArea)
		{
			Score = HealingArea->bIsActive ? 1.0f : 0.0f;
			It.SetScore(TestPurpose, FilterType, Score, 0.0f, 1.0f);

			It.ForceItemState(HealingArea->bIsActive ? EEnvItemStatus::Passed : EEnvItemStatus::Failed);
		}
	}
}

FText USTS_EnvQuery::GetDescriptionDetails() const
{
	FString Description = "Score when active : 1, Score when inactive : 0";
	return FText().FromString(Description);
}

FText USTS_EnvQuery::GetDescriptionTitle() const
{
	FString DescriptionTitle = "Testing for Healing area status";
	return FText().FromString(DescriptionTitle);
}
