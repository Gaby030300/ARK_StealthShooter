// Fill out your copyright notice in the Description page of Project Settings.


#include "STS_HealthComponent.h"

// Sets default values for this component's properties
USTS_HealthComponent::USTS_HealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	DefaultHealth = 100.0f;
	bDied = false;

}


// Called when the game starts
void USTS_HealthComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = DefaultHealth;

	AActor* ActorOwner = GetOwner();
	if (IsValid(ActorOwner)) 
	{
		ActorOwner->OnTakeAnyDamage.AddDynamic(this, &USTS_HealthComponent::HandleTakeAnyDamage);
	}	
}

void USTS_HealthComponent::HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if(Damage <= 0.0f)
	{
		return;
	}

	if (bDied)
	{
		return;
	}

	CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.0f, DefaultHealth);
	OnHealthChanged.Broadcast(this, CurrentHealth, -Damage, DamageType, InstigatedBy, DamageCauser);
	
	if (CurrentHealth == 0.0f) 
	{
		bDied = true;
		OnDeath.Broadcast(this, InstigatedBy, DamageCauser);
	}
}

void USTS_HealthComponent::Kill(AController* InstigatedBy, AActor* DamageCauser)
{
	if(bDied)
	{
		return;
	}

	CurrentHealth = 0.0f;
	bDied = true;
	OnDeath.Broadcast(this, InstigatedBy, DamageCauser);
}

void USTS_HealthComponent::Heal(const float HealAmount, AController* InstigatedBy, AActor* DamageCauser)
{
	if (bDied) 
	{
		return;
	}
	CurrentHealth = FMath::Clamp(CurrentHealth + HealAmount, 0.0f, DefaultHealth);
	OnHealthChanged.Broadcast(this, CurrentHealth, HealAmount, nullptr, InstigatedBy, DamageCauser);
}

bool USTS_HealthComponent::IsFriendly(const AActor* ActorA, const AActor* ActorB)
{
	if (ActorA == nullptr || ActorB == nullptr)
	{
		return true;
	}

	USTS_HealthComponent* HealthCompA = ActorA->FindComponentByClass<USTS_HealthComponent>();
	USTS_HealthComponent* HealthCompB = ActorB->FindComponentByClass<USTS_HealthComponent>();
	
	if (HealthCompA == nullptr || HealthCompB == nullptr)
	{
		return true;
	}
	return HealthCompA->TeamNumber == HealthCompB->TeamNumber;
}


 