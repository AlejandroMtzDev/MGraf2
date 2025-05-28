#include "CollisionPawn.h"
#include "Components/InputComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ACollisionPawn::ACollisionPawn()
{
    // Set this pawn to call Tick() every frame
    PrimaryActorTick.bCanEverTick = true;

    // Initialize movement speed
    speed = 500.0f;

    // Create and set up the collision component
    CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
    RootComponent = CollisionComponent;
    CollisionComponent->InitSphereRadius(40.0f);
    CollisionComponent->SetCollisionProfileName(TEXT("Pawn"));

    // Create and set up the mesh component
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    MeshComponent->SetupAttachment(RootComponent);

    // Load a simple cube mesh
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
    if (CubeMesh.Succeeded())
    {
        MeshComponent->SetStaticMesh(CubeMesh.Object);
    }
}

// Called when the game starts or when spawned
void ACollisionPawn::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ACollisionPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACollisionPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Bind input actions
    PlayerInputComponent->BindAxis("VerticalAxis", this, &ACollisionPawn::VerticalAxis);
    PlayerInputComponent->BindAxis("HorizontallAxis", this, &ACollisionPawn::HorizontalAxis);
}

void ACollisionPawn::HorizontalAxis(float value)
{
    float deltaTime = GetWorld()->GetDeltaSeconds();
    AddActorLocalOffset(FVector(0, value * speed * deltaTime, 0));
}

void ACollisionPawn::VerticalAxis(float value)
{
    float deltaTime = GetWorld()->GetDeltaSeconds();
    AddActorLocalOffset(FVector(value * speed * deltaTime, 0, 0));
}
