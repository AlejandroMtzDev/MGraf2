// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyPlayer.generated.h"

UCLASS()
class MGRAF2_API AMyPlayer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyPlayer();
	virtual void Tick(float DeltaTime) override;

	// UFUNCTION()
	// void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	// 	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	// 	const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* CollisionBox;

	UPROPERTY(EditAnywhere)
	float health;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

};
