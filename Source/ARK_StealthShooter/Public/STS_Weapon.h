// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STS_Weapon.generated.h"

class UStaticMeshComponent;
class UParticleSystem;
class USoundBase;

UCLASS()
class ARK_STEALTHSHOOTER_API ASTS_Weapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASTS_Weapon();

	void StartFire();

	void StopFire();


protected:

	void Fire();

protected:

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly) 
	float ShotDistance;	
	
	UPROPERTY(EditDefaultsOnly) 
	float ShotDamage;		
	
	UPROPERTY(EditDefaultsOnly)
	bool bDrawDebug;

	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = 0.0f)) 
	float RoundsPerMinute;

	float TimeBetweenShots;
	float LastFireTime;

	UPROPERTY(EditDefaultsOnly)
	UParticleSystem* ImpactEffect;	

	UPROPERTY(EditDefaultsOnly)
	UParticleSystem* MuzzleEffect;	
	
	UPROPERTY(EditDefaultsOnly)
	UParticleSystem* TracerEffect;

	UPROPERTY(EditDefaultsOnly)
	FName MuzzleSocketName;

	UPROPERTY(EditDefaultsOnly)
	FName TracerTargetName;

	UPROPERTY(EditDefaultsOnly)
	USoundBase* ShotSound;

	UPROPERTY(EditDefaultsOnly)
	float ShotLoudness;	

	UPROPERTY(EditDefaultsOnly)
	FVector MuzzleLocation;

	FTimerHandle TimerHandle_AutoFire;
	
	UPROPERTY(EditDefaultsOnly) 
	TSubclassOf<UDamageType> DamageType;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
