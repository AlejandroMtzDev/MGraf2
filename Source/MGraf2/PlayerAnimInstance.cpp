// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "ThirdPerson/FPV_Controller.h"

void UPlayerAnimInstance::UpdateAnimationProperties(float deltaSeconds)
{
	if (playerCharacter == nullptr)
	{
		playerCharacter = Cast<AFPV_Controller>(TryGetPawnOwner());
	}

	if (playerCharacter)
	{
		FVector velocity {playerCharacter->GetVelocity()};
		velocity.Z = 0;
		speed = velocity.Size();
	}
}

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	playerCharacter = Cast<AFPV_Controller>(TryGetPawnOwner());
}

