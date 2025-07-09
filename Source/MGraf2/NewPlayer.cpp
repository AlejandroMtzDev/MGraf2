// Fill out your copyright notice in the Description page of Project Settings.


#include "NewPlayer.h"
#include "KeyObject.h"
#include "Components/SphereComponent.h"

// Sets default values
ANewPlayer::ANewPlayer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PickUpRange = CreateDefaultSubobject<USphereComponent>(TEXT("PickUpRange"));
	PickUpRange->SetupAttachment(RootComponent);
	PickUpRange->InitSphereRadius(200.0f);
	PickUpRange->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	// PickUpRange->OnComponentBeginOverlap.AddDynamic(this, &ANewPlayer::OnOverlapBegin);
	// PickUpRange->OnComponentEndOverlap.AddDynamic(this, &ANewPlayer::OnOverlapEnd);
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

// void ANewPlayer::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
// {
// 	if (AKeyObject* key = Cast<AKeyObject>(OtherActor))
// 	{
// 		OverlappingObjects.Add(key);
// 		key->Pick();
// 	}
// }
//
// void ANewPlayer::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
// {
// 	if (AKeyObject* key = Cast<AKeyObject>(OtherActor))
// 	{
// 		OverlappingObjects.Remove(key);
// 	}
// }
//
// void ANewPlayer::PickUpKey()
// {
// 	if (OverlappingObjects.Num() > 0)
// 	{
// 		AKeyObject* key = OverlappingObjects[0];
// 		key->Pick();
// 		OverlappingObjects.Remove(key);
// 	}
// }