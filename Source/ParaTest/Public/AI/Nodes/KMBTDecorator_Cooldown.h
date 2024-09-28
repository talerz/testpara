// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "BehaviorTree/Decorators/BTDecorator_Cooldown.h"
#include "KMBTDecorator_Cooldown.generated.h"

/**
 * 
 */
UCLASS()
class PARATEST_API UKMBTDecorator_Cooldown : public UBTDecorator_Cooldown
{
	GENERATED_BODY()
	UKMBTDecorator_Cooldown();
public:
	UPROPERTY(Category=Decorator, EditAnywhere)
	FGameplayAttribute AttackCooldown;
	
	mutable float AttributeCooldown = 5.f;
	
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual FString GetStaticDescription() const override;
	virtual void DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const override;
};
