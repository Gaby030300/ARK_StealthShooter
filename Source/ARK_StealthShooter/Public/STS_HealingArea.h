// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STS_HealingArea.generated.h"

class UStaticMeshComponent;
class ASTS_BaseCharacter;

UCLASS()
class ARK_STEALTHSHOOTER_API ASTS_HealingArea : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* AreaMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	float HealingAmount;

	UPROPERTY(EditDefaultsOnly)
	float CoolDown;

	FTimerHandle TimerHandle_CoolDown;

	UFUNCTION()
	void Heal(ASTS_BaseCharacter* HealCharacter);

	UFUNCTION()
	void Reset();

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
public:	
	UPROPERTY()
	uint8 bIsActive : 1;
	// Sets default values for this actor's properties
	ASTS_HealingArea();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
