// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPV_Controller.generated.h"

UCLASS()
class MGRAF2_API AFPV_Controller : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPV_Controller();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* cameraComponent;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float inputVector);
	void MoveRight(float inputVector);
	void TurnCamera(float inputVector);
	void LookUp(float inputVector);

	void StartAttack();

	UFUNCTION(BlueprintCallable)
	void LineTrace();

	UPROPERTY(BlueprintReadWrite)
	bool isAttacking;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* swordMesh;

	UPROPERTY(EditAnywhere)
	class UAnimSequence* attackAnimation;
};
