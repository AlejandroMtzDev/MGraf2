// Fill out your copyright notice in the Description page of Project Settings.


#include "BreakableObstacle.h"
#include "Projectile.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABreakableObstacle::ABreakableObstacle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("RootComponent"));
	BoxComponent->InitBoxExtent(FVector(1, 1, 1));
	BoxComponent->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	RootComponent = BoxComponent;

	BoxComponent->OnComponentHit.AddDynamic(this, &ThisClass::OnProjectileImpact);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(RootComponent);

	if (CubeMesh.Succeeded())
	{
		MeshComponent->SetStaticMesh(CubeMesh.Object);
	}
	
	hitCount = 0;
}

// Called when the game starts or when spawned
void ABreakableObstacle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABreakableObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABreakableObstacle::OnProjectileImpact(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (AProjectile* hit = Cast<AProjectile>(OtherActor))
	{
		if (hitCount >= 3)
		{
			Destroy();
		}
		
		hitCount += 1;
	}
}


