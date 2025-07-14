// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"


// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	bIsUsingWeapon = false;
}

// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UWeaponComponent::InitializeComponent(USceneComponent* skeleton, UStaticMeshComponent* mesh, FVector start, FVector end, FName hand, FName scabbard)
{
	skeletalMesh = skeleton;
	weaponMesh = mesh;
	startLocation = start;
	endLocation = end;
	handPosition = hand;
	scabbardPosition = scabbard;
}

void UWeaponComponent::UseWeapon()
{
	weaponMesh->AttachToComponent(skeletalMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, handPosition);
	bIsUsingWeapon = true;
}

void UWeaponComponent::SheathWeapon()
{
	weaponMesh->AttachToComponent(skeletalMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, scabbardPosition);
	bIsUsingWeapon = false;
}

