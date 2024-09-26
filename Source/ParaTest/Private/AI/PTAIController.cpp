// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/PTAIController.h"

#include "AI/PTPatrolPoint.h"
#include "AI/PTEnemyCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Player/PTPlayerCharacter.h"

APTAIController::APTAIController()
{
	AIBehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	AIBlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoardComp"));

	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));
}

void APTAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (!AIBehaviorTreeComponent || !AIBlackboardComponent || !AIBehaviorTree)
		return;

	AIBlackboardComponent->InitializeBlackboard(*AIBehaviorTree->BlackboardAsset);
	AIBehaviorTreeComponent->StartTree(*AIBehaviorTree);

	//Setup BB values 
	if (const APTEnemyCharacter* AIChar = Cast<APTEnemyCharacter>(InPawn))
	{
		Blackboard->SetValueAsFloat("MaxNormalAttackRadius", AIChar->MaxNormalAttackRadius);
		Blackboard->SetValueAsFloat("MaxFireAttackRadius", AIChar->MaxFireAttackRadius);

		Blackboard->SetValueAsFloat("MinNormalAttackRadius", AIChar->MinNormalAttackRadius);
		Blackboard->SetValueAsFloat("MinFireAttackRadius", AIChar->MinFireAttackRadius);
	}

	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &APTAIController::OnTargetPerceptionUpdated);
	AIPerceptionComponent->OnTargetPerceptionForgotten.AddDynamic(this, &APTAIController::OnTargetPerceptionForgotten);
}

void APTAIController::OnUnPossess()
{
	Super::OnUnPossess();
}

void APTAIController::UpdatePatrolPoint(const TObjectPtr<APTPatrolPoint>& NewPatrolPoint)
{
	if (NewPatrolPoint == nullptr)
	{
		return;
	}

	if (IsValid(Blackboard))
	{
		Blackboard->SetValueAsObject(BBKey_PatrolPoint, NewPatrolPoint);
	}
}

void APTAIController::OnTargetPerceptionUpdated(AActor* Actor, struct FAIStimulus Stimulus)
{
	//Clear Target if not sensed
	if(!Stimulus.WasSuccessfullySensed())
	{
		UpdateTargetActor(nullptr);
	}
	if (!IsValid(Actor) || !Cast<APTPlayerCharacter>(Actor))
	{
		return;
	}
	UpdateTargetActor(Actor);
}

void APTAIController::OnTargetPerceptionForgotten(AActor* Actor)
{
	if (!IsValid(Actor))
	{
		return;
	}
	if (Actor == CurrentTargetActor)
	{
		//clear target aggro
		UpdateTargetActor(nullptr);
	}
}

void APTAIController::ChangeStaggeredState(bool bStagger)
{
	if (Blackboard != nullptr)
	{
		if (Blackboard->GetValueAsBool("Staggered") != bStagger)
		{
			Blackboard->SetValueAsBool("Staggered", bStagger);
		}
	}
}

void APTAIController::UpdateTargetActor(const TObjectPtr<AActor>& NewTarget)
{
	if (!IsValid(NewTarget))
	{
		Blackboard->SetValueAsObject(BBTarget, nullptr);
	}
	if (CurrentTargetActor == NewTarget)
	{
		return;
	}
	else
	{
		CurrentTargetActor = NewTarget;
		if (IsValid(Blackboard))
		{
			Blackboard->SetValueAsObject(BBTarget, NewTarget);
		}
	}
}
