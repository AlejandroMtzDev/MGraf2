// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"


// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	bCanTakeDamage = true;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType,
									 FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::Die()
{
	GetOwner()->Destroy();
}

void UHealthComponent::TakeDamage(int damage)
{
	Health -= damage;

	if (bCanTakeDamage)
	{
		Health += damage;
		bCanTakeDamage = false;

		FTimerHandle invincibility;

		GetWorld()->GetTimerManager().SetTimer(invincibility, this, &UHealthComponent::AllowTakeDamage, 0.5f, false);
	}

	if (Health <= 0)
	{
		Die();
	}
}

void UHealthComponent::AllowTakeDamage()
{
	bCanTakeDamage = true;
}