// Fill out your copyright notice in the Description page of Project Settings.


#include "STS_Enemy.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void ASTS_Enemy::SetEnemyStatus(ESTS_EnemyStatus NewEnemyStatus)
{
	float Speed = EnemySpeedMap[NewEnemyStatus];
	GetCharacterMovement()->MaxWalkSpeed = Speed;

	BP_SetEnemyStatus(NewEnemyStatus);
}
