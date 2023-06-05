// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STS_HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FOnHealthChanged, USTS_HealthComponent*, HealthComp, float, Health, float, HealthDelta, const class UDamageType*, DamageType, class AController*, InstigatedBy, AActor*, DamageCauser);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnDeath, USTS_HealthComponent*, HealthComp, class AController*, InstigatedBy, AActor*, Killer);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARK_STEALTHSHOOTER_API USTS_HealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USTS_HealthComponent();

	UPROPERTY(EditDefaultsOnly)
	uint8 TeamNumber;

	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;	
	
	UPROPERTY(BlueprintAssignable)
	FOnDeath OnDeath;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;	

	UPROPERTY(EditDefaultsOnly)
	float DefaultHealth;	
	
	UPROPERTY(BlueprintReadOnly)
	bool bDied;

	UPROPERTY(BlueprintReadOnly)
	float CurrentHealth;

	UFUNCTION()
	void HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

public:

	UFUNCTION(BlueprintCallable)
	void Kill(AController* InstigatedBy, AActor* DamageCauser);	
	
	UFUNCTION(BlueprintCallable)
	void Heal(const float HealAmount, AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION()
	static bool IsFriendly(const AActor* ActorA, const AActor* ActorB);
};
