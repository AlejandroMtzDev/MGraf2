// Fill out your copyright notice in the Description page of Project Settings.


#include "IpvMultiCharacter.h"
#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"

// Sets default values
AIpvMultiCharacter::AIpvMultiCharacter()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MaxHealth = 100.0f;
	CurrentHealth = MaxHealth;
}

void AIpvMultiCharacter::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AIpvMultiCharacter, CurrentHealth);
}

// Called when the game starts or when spawned
void AIpvMultiCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIpvMultiCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AIpvMultiCharacter::OnRep_CurrentHealth()
{
	OnHealthUpdate();
}

void AIpvMultiCharacter::OnHealthUpdate()
{
	////Client-specific functionality
	//if (IsLocallyControlled())
	//{
	//	FString healthMessage = FString::Printf(TEXT("You now have %f health remaining."), CurrentHealth);
	//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, healthMessage);
	// 
	//	if (CurrentHealth <= 0)
	//	{
	//		FString deathMessage = FString::Printf(TEXT("You have been killed."));
	//		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, deathMessage);
	//	}
	//}
	// 
	////Server-specific functionality
	//if (GetLocalRole() == ROLE_Authority)
	//{
	//	FString healthMessage = FString::Printf(TEXT("%s now has %f health remaining."), *GetFName().ToString(), CurrentHealth);
	//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, healthMessage);
	//}
	 
	//Functions that occur on all machines.
	/*
		Any special functionality that should occur as a result of damage or death should be placed here.
	*/
}


