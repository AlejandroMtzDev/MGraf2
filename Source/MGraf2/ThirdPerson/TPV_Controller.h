// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TPV_Controller.generated.h"

UCLASS()
class MGRAF2_API ATPV_Controller : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATPV_Controller();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* cameraComponent;

	void SwapWeapon();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float inputVector);
	void MoveRight(float inputVector);
	void TurnCamera(float inputVector);
	void LookUp(float inputVector);

	void UseSword();
	void UseAxe();
	
	void StartAttack();

	UFUNCTION(BlueprintCallable)
	void LineTrace();

	UPROPERTY(BlueprintReadWrite)
	bool isAttacking;

	bool isUsingSword;
	bool isUsingAxe;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* swordMesh;
	
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* axeMesh;

	UPROPERTY(EditAnywhere)
	class UAnimSequence* attackAnimation;

	UPROPERTY(EditAnywhere)
	class UAnimSequence* axeAttackAnimation;

	UPROPERTY(EditAnywhere)
	class UWeaponComponent* axeComponent;

	UPROPERTY(EditAnywhere)
	class UWeaponComponent* swordComponent;
	
	UFUNCTION()
	void OnAttackEnded(UAnimMontage* Montage, bool bInterrupted);

	UPROPERTY(EditAnywhere)
	int damage;

	void ResetAttackState();

	FTimerHandle attackResetHandle;
	FTimerHandle swapWeaponHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* attackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* axeAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* swapWeaponMontage;
};
