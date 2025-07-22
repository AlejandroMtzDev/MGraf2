// Fill out your copyright notice in the Description page of Project Settings.


#include "TFindRandomLocation.h"

#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MGraf2/AI/EnemyController.h"

UTFindRandomLocation::UTFindRandomLocation(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Find random location";
}

EBTNodeResult::Type UTFindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto* const ctlr = Cast<AEnemyController>(OwnerComp.GetAIOwner()))
	{
		if (auto* const enemy = ctlr->GetPawn())
		{
			auto const origin = enemy->GetActorLocation();

			if (auto* const navSys = UNavigationSystemV1::GetCurrent(GetWorld()))
			{
				FNavLocation location;

				if (navSys->GetRandomPointInNavigableRadius(origin, searchRadius, location))
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), location.Location);
				}

				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

				return EBTNodeResult::Succeeded;
			}
		}
	}

	return EBTNodeResult::Failed;
}


