// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyObject.h"
#include "Components/SphereComponent.h"

// Sets default values
AKeyObject::AKeyObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	RootComponent = CollisionComponent;
	CollisionComponent->InitSphereRadius(40.0f);
	CollisionComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
}

// Called when the game starts or when spawned
void AKeyObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKeyObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKeyObject::Pick()
{
	Destroy();
}

