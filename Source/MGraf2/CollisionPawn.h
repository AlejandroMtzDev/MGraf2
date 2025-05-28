#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CollisionPawn.generated.h"

UCLASS()
class MGRAF2_API ACollisionPawn : public APawn
{
    GENERATED_BODY()

public:
    // Sets default values for this pawn's properties
    ACollisionPawn();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    // Function to handle movement
    void VerticalAxis(float value);
    void HorizontalAxis(float value);

    // Collision component
    UPROPERTY(VisibleAnywhere, Category = "Collision")
    class USphereComponent* CollisionComponent;

    // Mesh component for the pawn
    UPROPERTY(VisibleAnywhere, Category = "Mesh")
    class UStaticMeshComponent* MeshComponent;

    // Movement speed
    UPROPERTY(EditAnywhere, Category = "Movement")
    float speed;
};