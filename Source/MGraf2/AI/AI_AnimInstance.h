// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "Animation/AnimInstance.h"
#include "AI_AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MGRAF2_API UAI_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(blueprintCallable)
	void UpdateAnimationProperties(float deltaSeconds);

	virtual void NativeInitializeAnimation() override;

private:
	UPROPERTY(visibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	AEnemy* enemy;

	UPROPERTY(visibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float speed;
};
