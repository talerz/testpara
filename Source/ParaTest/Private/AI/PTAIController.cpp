// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/PTAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

APTAIController::APTAIController()
{
	AIBehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	AIBlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoardComp"));
}

void APTAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (!AIBehaviorTreeComponent || !AIBlackboardComponent || !AIBehaviorTree)
		return;

	AIBlackboardComponent->InitializeBlackboard(*AIBehaviorTree->BlackboardAsset);
	AIBehaviorTreeComponent->StartTree(*AIBehaviorTree);
	if (const APTAIController* AIChar = Cast<APTAIController>(InPawn))
	{
		//Setup BB values 
	}
}
