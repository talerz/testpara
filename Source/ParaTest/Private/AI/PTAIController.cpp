// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/PTAIController.h"

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

void APTAIController::OnTargetPerceptionUpdated(AActor* Actor, struct FAIStimulus Stimulus)
{
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
		//log that sth went wrong
		return;
	}
	if (Actor == CurrentTargetActor)
	{
		//clear target aggro
		UpdateTargetActor(nullptr);
	}
}

void APTAIController::UpdateTargetActor(const TObjectPtr<AActor>& NewTarget)
{
	if (!IsValid(NewTarget))
	{
		//Clear target - lost, killed etc
	}
	if (CurrentTargetActor == NewTarget)
	{
		//Log? No need to change target 
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
