// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NewPlayer.generated.h"

UCLASS()
class MGRAF2_API ANewPlayer : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANewPlayer();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	void VerticalAxis(float value);
	void HorizontalAxis(float value);
	UPROPERTY(EditAnywhere)
	float velocity;

	void RotateRight();
	void RotateLeft();
	UPROPERTY(EditAnywhere)
	float rotationRate;

	void FirePressed();
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> spawnObject;

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* PickUpRange;

	TArray<class AKey*> OverlappingObjects;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void PickUpKey();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
