// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_AnimInstance.h"

void UAI_AnimInstance::UpdateAnimationProperties(float deltaSeconds)
{
	if (enemy == nullptr)
	{
		enemy = Cast<AEnemy>(TryGetPawnOwner());
	}

	if (enemy)
	{
		FVector velocity {enemy->GetVelocity()};
		velocity.Z = 0;
		speed = velocity.Size();
	}
}

void UAI_AnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	enemy = Cast<AEnemy>(TryGetPawnOwner());
}

