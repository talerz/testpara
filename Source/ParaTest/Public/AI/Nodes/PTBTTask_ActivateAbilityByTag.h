// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySpec.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "PTBTTask_ActivateAbilityByTag.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class PARATEST_API UPTBTTask_ActivateAbilityByTag : public UBTTaskNode
{
	GENERATED_BODY()
	public:
	
	UPTBTTask_ActivateAbilityByTag(const FObjectInitializer& ObjectInitializer);

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	EBTNodeResult::Type ActivateAbilityByTag(const TObjectPtr<AActor>& ControlledActor, const FGameplayTagContainer& Tag);

	bool TryActivateAbilityByTag(UAbilitySystemComponent* AbilitySystem, const FGameplayTagContainer& Tags, FGameplayAbilitySpec& ActivatedAbilitySpec);
	
	FString GetStaticDescription() const;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTagContainer AbilityTag;
};
