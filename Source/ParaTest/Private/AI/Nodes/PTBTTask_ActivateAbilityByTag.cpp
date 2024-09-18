// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Nodes/PTBTTask_ActivateAbilityByTag.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"


UPTBTTask_ActivateAbilityByTag::UPTBTTask_ActivateAbilityByTag(const FObjectInitializer& ObjectInitializer)
{
	NodeName = TEXT("ActivateAbilityByTag");

	INIT_TASK_NODE_NOTIFY_FLAGS();
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UPTBTTask_ActivateAbilityByTag::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (OwnerComp.GetOwner() == nullptr || !OwnerComp.GetAIOwner())
	{
		return EBTNodeResult::Failed;
	}
	if (const TObjectPtr<AActor> ControlledPawn = OwnerComp.GetAIOwner()->GetPawn())
	{
		const TObjectPtr<UBlackboardComponent> BlackboardComponent = OwnerComp.GetBlackboardComponent();

		if (!BlackboardComponent)
		{
			return EBTNodeResult::Failed;
		}

		return ActivateAbilityByTag(ControlledPawn, AbilityTag);
	}
	return EBTNodeResult::Failed;
}

EBTNodeResult::Type UPTBTTask_ActivateAbilityByTag::ActivateAbilityByTag(const TObjectPtr<AActor>& ControlledActor,
                                                                         const FGameplayTagContainer& Tag)
{
	if (!IsValid(ControlledActor))
	{
		return EBTNodeResult::Failed;
	}
	if (UAbilitySystemComponent* AbilitySystem = Cast<UAbilitySystemComponent>(
		UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(ControlledActor)))
	{
		FGameplayAbilitySpec ActivatedAbilitySpec;
		if (!TryActivateAbilityByTag(AbilitySystem, Tag, ActivatedAbilitySpec))
		{
			return EBTNodeResult::Failed;
		}
		if (!ActivatedAbilitySpec.Ability)
		{
			return EBTNodeResult::Failed;
		}
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}

bool UPTBTTask_ActivateAbilityByTag::TryActivateAbilityByTag(UAbilitySystemComponent* AbilitySystem,
                                                             const FGameplayTagContainer& Tags,
                                                             FGameplayAbilitySpec& ActivatedAbilitySpec)
{
	if (AbilitySystem == nullptr)
	{
		return false;
	}

	//Ability System Component TryActivateAbilityByTag 
	TArray<FGameplayAbilitySpec*> AbilitiesToActivatePtrs;
	AbilitySystem->GetActivatableGameplayAbilitySpecsByAllMatchingTags(Tags, AbilitiesToActivatePtrs);
	if (AbilitiesToActivatePtrs.Num() < 1)
	{
		return false;
	}

	// Convert from pointers (which can be reallocated, since they point to internal data) to copies of that data
	TArray<FGameplayAbilitySpec> AbilitiesToActivate;
	AbilitiesToActivate.Reserve(AbilitiesToActivatePtrs.Num());
	Algo::Transform(AbilitiesToActivatePtrs, AbilitiesToActivate,
	                [](FGameplayAbilitySpec* SpecPtr) { return *SpecPtr; });

	bool bSuccess = false;

	//TODO: Instead of getting 1st found, AbilitySystem should be extended 
	ensure(IsValid(AbilitiesToActivate[0].Ability));

	bSuccess |= AbilitySystem->TryActivateAbility(AbilitiesToActivate[0].Handle, true);


	if (bSuccess)
	{
		ActivatedAbilitySpec = AbilitiesToActivate[0];
		return bSuccess;
	}
	return false;
}

FString UPTBTTask_ActivateAbilityByTag::GetStaticDescription() const
{
	return FString::Printf(TEXT("Ability Tag: %s"), *AbilityTag.ToStringSimple(false));
}
