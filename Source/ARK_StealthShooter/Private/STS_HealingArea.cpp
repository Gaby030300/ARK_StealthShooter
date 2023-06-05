// Fill out your copyright notice in the Description page of Project Settings.


#include "STS_HealingArea.h"
#include "Components/StaticMeshComponent.h"
#include <STS_BaseCharacter.h>
#include <STS_HealthComponent.h>

// Sets default values
ASTS_HealingArea::ASTS_HealingArea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	AreaMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HealingArea"));
	SetRootComponent(AreaMeshComponent);

	bIsActive = true;

}

void ASTS_HealingArea::BeginPlay()
{
	Super::BeginPlay();
	if (AreaMeshComponent) 
	{
		AreaMeshComponent -> OnComponentBeginOverlap.AddDynamic(this, &ASTS_HealingArea::OnOverlap);
	}
}

void ASTS_HealingArea::Heal(ASTS_BaseCharacter* HealCharacter)
{
	USTS_HealthComponent* HealthComponent = HealCharacter->HealthComponent;
	if (HealthComponent)
	{
		HealthComponent->Heal(HealingAmount, nullptr, this);
	}
	bIsActive = false;
	AreaMeshComponent->SetVisibility(false);
	AreaMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetWorldTimerManager().SetTimer(TimerHandle_CoolDown, this, &ASTS_HealingArea::Reset, CoolDown);

}

void ASTS_HealingArea::Reset()
{
	bIsActive = true;
	AreaMeshComponent->SetVisibility(true);
	AreaMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void ASTS_HealingArea::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ASTS_BaseCharacter* OverlappingCharacter = Cast<ASTS_BaseCharacter>(OtherActor);
	if (OverlappingCharacter) 
	{
		Heal(OverlappingCharacter);
	}
}
