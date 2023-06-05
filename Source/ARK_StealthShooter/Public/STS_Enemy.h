// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "STS_BaseCharacter.h"
#include "STS_Enemy.generated.h"

UENUM(BlueprintType)
enum class ESTS_EnemyStatus : uint8 
{
	EnemyStatus_Patrol = 0          UMETA(DisplayName = "Patrol"),
	EnemyStatus_Investigating = 1   UMETA(DisplayName = "Investigating"),
	EnemyStatus_Combat = 2          UMETA(DisplayName = "Combat"),
};

class ASTS_PatrolActor;

UCLASS()
class ARK_STEALTHSHOOTER_API ASTS_Enemy : public ASTS_BaseCharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ASTS_PatrolActor* PatrolActorReference;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<ESTS_EnemyStatus, float> EnemySpeedMap;

	UFUNCTION(BlueprintCallable)
	void SetEnemyStatus(ESTS_EnemyStatus NewEnemyStatus);

protected:

	UFUNCTION(BlueprintImplementableEvent)
	void BP_SetEnemyStatus(ESTS_EnemyStatus NewEnemyStatus);

};
