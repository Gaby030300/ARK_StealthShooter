// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "STS_EnvQuery.generated.h"


UCLASS()
class ARK_STEALTHSHOOTER_API USTS_EnvQuery : public UEnvQueryTest
{
	GENERATED_BODY()
	USTS_EnvQuery(const FObjectInitializer& ObjectInitializer);

	virtual void RunTest(FEnvQueryInstance& QueryInstance) const override; 
	virtual FText GetDescriptionDetails() const override;
	virtual FText GetDescriptionTitle() const override;	
};
