// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"

#include "Enemy.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MGraf2/ThirdPerson/TPV_Controller.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

AEnemyController::AEnemyController(FObjectInitializer const& ObjectInitializer)
{
	SetUpPerceptionSystem();
}

// Called when the game starts or when spawned
void AEnemyController::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (AEnemy* const enemy = Cast<AEnemy>(InPawn))
	{
		if (UBehaviorTree* const tree = enemy->GetBehaviourTree())
		{
			UBlackboardComponent* b;
			UseBlackboard(tree->BlackboardAsset, b);

			Blackboard = b;

			RunBehaviorTree(tree);
		}
	}
}

void AEnemyController::SetUpPerceptionSystem()
{
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));

	if (SightConfig)
	{
		SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
		SightConfig->SightRadius = 1000.0f;
		SightConfig->LoseSightRadius = SightConfig->SightRadius + 250;
		SightConfig->PeripheralVisionAngleDegrees = 45.0f;
		SightConfig->SetMaxAge(5.0f);
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

		GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
		GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyController::OnTargetDetected);
		GetPerceptionComponent()->ConfigureSense((*SightConfig));
	}
}

void AEnemyController::OnTargetDetected(AActor* actor, FAIStimulus const stimulus)
{
	if (auto* const player = Cast<ATPV_Controller>(actor))
	{
		if (stimulus.WasSuccessfullySensed())
		{
			GetBlackboardComponent()->SetValueAsObject("TargetActor", player);	
		}
		else
		{
			GetBlackboardComponent()->SetValueAsObject("TargetActor", nullptr);
		}
	}
}

// Called every frame
void AEnemyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

