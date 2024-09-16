// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PTAIController.generated.h"

/**
 * 
 */
UCLASS()
class PARATEST_API APTAIController : public AAIController
{
	GENERATED_BODY()
public:
	APTAIController();
	virtual void OnPossess(APawn* InPawn) override;
protected:
	UPROPERTY()
	class UBehaviorTreeComponent* AIBehaviorTreeComponent;
	
	UPROPERTY(BlueprintReadOnly)
	class UBlackboardComponent* AIBlackboardComponent;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	class UBehaviorTree* AIBehaviorTree;
};
