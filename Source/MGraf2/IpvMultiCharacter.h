// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IpvMultiCharacter.generated.h"

UCLASS()
class MGRAF2_API AIpvMultiCharacter : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AIpvMultiCharacter();
	void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** The player's maximum health. This is the highest value of their health can be. This value is a value of the player's health, which starts at when spawned.*/
	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float MaxHealth;
	 
	/** The player's current health. When reduced to 0, they are considered dead.*/
	UPROPERTY(ReplicatedUsing = OnRep_CurrentHealth)
	float CurrentHealth;
	 
	/** RepNotify for changes made to current health.*/
	UFUNCTION()
	void OnRep_CurrentHealth();

	void OnHealthUpdate();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
