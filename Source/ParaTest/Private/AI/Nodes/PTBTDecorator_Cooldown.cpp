// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Nodes/PTBTDecorator_Cooldown.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "AIController.h"

UPTBTDecorator_Cooldown::UPTBTDecorator_Cooldown()
{
	NodeName = "Attribute Based Cooldown";
	INIT_DECORATOR_NODE_NOTIFY_FLAGS();
	CoolDownTime = 5.0f;

	// aborting child nodes doesn't makes sense, cooldown starts after leaving this branch
	bAllowAbortChildNodes = false;
}

bool UPTBTDecorator_Cooldown::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	if (OwnerComp.GetOwner() == nullptr || !OwnerComp.GetAIOwner())
	{
		return false;
	}
	if (const TObjectPtr<AActor> ControlledPawn = OwnerComp.GetAIOwner()->GetPawn())
	{
		if (UAbilitySystemComponent* AbilitySystem = Cast<UAbilitySystemComponent>(
			UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(ControlledPawn)))
		{
			bool bFound = false;
			AttributeCooldown = AbilitySystem->GetGameplayAttributeValue(AttackCooldown, bFound);
			if (!bFound)
			{
				AttributeCooldown = CoolDownTime;
			}
		}
	}

	FBTCooldownDecoratorMemory* DecoratorMemory = CastInstanceNodeMemory<FBTCooldownDecoratorMemory>(NodeMemory);
	const double RecalcTime = (OwnerComp.GetWorld()->GetTimeSeconds() - AttributeCooldown);
	return RecalcTime >= DecoratorMemory->LastUseTimestamp;
}

void UPTBTDecorator_Cooldown::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	FBTCooldownDecoratorMemory* DecoratorMemory = CastInstanceNodeMemory<FBTCooldownDecoratorMemory>(NodeMemory);
	if (!DecoratorMemory->bRequestedRestart)
	{
		const double RecalcTime = (OwnerComp.GetWorld()->GetTimeSeconds() - AttributeCooldown);
		if (RecalcTime >= DecoratorMemory->LastUseTimestamp)
		{
			DecoratorMemory->bRequestedRestart = true;
			OwnerComp.RequestExecution(this);
		}
	}
}

FString UPTBTDecorator_Cooldown::GetStaticDescription() const
{
	// basic info: result after time
	return FString::Printf(TEXT("Lock for %s after execution and return %s"),
	                       *AttackCooldown.GetName(), *UBehaviorTreeTypes::DescribeNodeResult(EBTNodeResult::Failed));
}

void UPTBTDecorator_Cooldown::DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
                                                    EBTDescriptionVerbosity::Type Verbosity,
                                                    TArray<FString>& Values) const
{
	Super::DescribeRuntimeValues(OwnerComp, NodeMemory, Verbosity, Values);

	FBTCooldownDecoratorMemory* DecoratorMemory = CastInstanceNodeMemory<FBTCooldownDecoratorMemory>(NodeMemory);
	const double TimePassed = OwnerComp.GetWorld()->GetTimeSeconds() - DecoratorMemory->LastUseTimestamp;

	if (TimePassed < AttributeCooldown)
	{
		Values.Add(FString::Printf(TEXT("%s in %ss"),
		                           (FlowAbortMode == EBTFlowAbortMode::None) ? TEXT("unlock") : TEXT("restart"),
		                           *FString::SanitizeFloat(AttributeCooldown - TimePassed)));
	}
}
