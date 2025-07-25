// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MGRAF2_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UWeaponComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	FVector startLocation;
    FVector endLocation;

	FName handPosition;
	FName scabbardPosition;

	USceneComponent* skeletalMesh;

	UStaticMeshComponent* weaponMesh;

	bool bIsUsingWeapon;
	
	void InitializeComponent(USceneComponent* skeleton, UStaticMeshComponent* mesh, FVector start, FVector end, FName hand, FName scabbard);

	void UseWeapon();
	void SheathWeapon();
};
