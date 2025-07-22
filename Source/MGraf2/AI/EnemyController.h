// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionTypes.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "EnemyController.generated.h"

UCLASS()
class MGRAF2_API AEnemyController : public AAIController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	explicit AEnemyController(FObjectInitializer const& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

	class UAISenseConfig_Sight* SightConfig;

	UFUNCTION()
	void OnTargetDetected(AActor* actor, FAIStimulus const stimulus);
	
	void SetUpPerceptionSystem();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
