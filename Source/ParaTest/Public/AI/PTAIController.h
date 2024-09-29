// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PTAIController.generated.h"

class UBehaviorTreeComponent;
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

	virtual void OnUnPossess() override;

	void UpdatePatrolPoint(const TObjectPtr<class APTPatrolPoint>& NewPatrolPoint) const;

protected:
	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> AIBehaviorTreeComponent;

	UPROPERTY(BlueprintReadOnly, Category = "AI")
	TObjectPtr<UBlackboardComponent> AIBlackboardComponent;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TObjectPtr<UBehaviorTree> AIBehaviorTree;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	TObjectPtr<UAIPerceptionComponent> AIPerceptionComponent;

	UPROPERTY()
	TObjectPtr<AActor> CurrentTargetActor = nullptr;

	UFUNCTION(BlueprintCallable)
	void OnTargetPerceptionUpdated(AActor* Actor, struct FAIStimulus Stimulus);

	UFUNCTION(BlueprintCallable)
	void OnTargetPerceptionForgotten(AActor* Actor);

	//BB keys names
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BlackBoard")
	FName BBTarget = TEXT("Target");
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BlackBoard")
	FName BBStaggered = TEXT("bStaggered");
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BlackBoard")
	FName BBKey_PatrolPoint = FName("PatrolPoint");
	//~~BB keys names

private:
	void UpdateTargetActor(const TObjectPtr<AActor>& NewTarget);
};
