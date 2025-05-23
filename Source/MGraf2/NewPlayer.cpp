// Fill out your copyright notice in the Description page of Project Settings.


#include "NewPlayer.h"

// Sets default values
ANewPlayer::ANewPlayer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANewPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANewPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANewPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	InputComponent->BindAxis("VerticalAxis", this, &ANewPlayer::VerticalAxis);
	InputComponent->BindAxis("HorizontalAxis", this, &ANewPlayer::HorizontalAxis);
	InputComponent->BindAction("Fire", IE_Pressed, this, &ANewPlayer::FirePressed);
	InputComponent->BindAction("RotateLeft", IE_Repeat, this, &ANewPlayer::RotateLeft);
	InputComponent->BindAction("RotateRight", IE_Repeat, this, &ANewPlayer::RotateRight);
}

void ANewPlayer::HorizontalAxis(float value)
{
	float deltaTime = GetWorld()->GetDeltaSeconds();
	AddActorLocalOffset(FVector(0, value * velocity * deltaTime, 0));
}

void ANewPlayer::RotateRight()
{
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += rotationRate;
	SetActorRotation(NewRotation);
}

void ANewPlayer::RotateLeft()
{
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw -= rotationRate;
	SetActorRotation(NewRotation);
}

void ANewPlayer::VerticalAxis(float value)
{
	float deltaTime = GetWorld()->GetDeltaSeconds();
	AddActorLocalOffset(FVector(value * velocity * deltaTime, 0, 0));
}

void ANewPlayer::FirePressed()
{
	GetWorld()->SpawnActor<AActor>(spawnObject, GetActorLocation(), GetActorRotation());
}

