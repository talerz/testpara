// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Anim/PTStaggerComponent.h"

#include "AbilitySystemComponent.h"

UPTStaggerComponent::UPTStaggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UPTStaggerComponent::BeginPlay()
{
	//No need to tick all the time
	SetComponentTickEnabled(false);
	Super::BeginPlay();
}

bool UPTStaggerComponent::CanApplyStagger() const
{
	//Don't start stagger if already staggered or while immune
	if (bStaggered || !IsValid(StaggerSettings) || CurrentStaggerImmunityTime > 0.f)
	{
		return false;
	}
	return true;
}

void UPTStaggerComponent::StartStagger()
{
	if(CanApplyStagger() == false)
	{
		return;
	}
	if(IsValid(StaggerSettings))
	{
		CurrentStaggerTime = StaggerSettings->StaggerTimeDuration;
		CurrentStaggerImmunityTime = StaggerSettings->StaggerImmunityDuration;

		if(IsValid(GetOwner()))
		{
			TObjectPtr<UAbilitySystemComponent> AbilitySystem = GetOwner()->GetComponentByClass<UAbilitySystemComponent>();
			if(AbilitySystem != nullptr)
			{
				AbilitySystem->AddLooseGameplayTag(StaggerSettings->StaggerTag);
			}
		}
	}
	bStaggered = true;
	SetComponentTickEnabled(true);
}

void UPTStaggerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Just decrease Stagger time, till it reaches 0
	if (CurrentStaggerTime > 0.f)
	{
		CurrentStaggerTime -= DeltaTime;

		return;
	}
	if (bStaggered)
	{
		bStaggered = false;

		//Remove Stagger Gameplay tag, when stagger time finished
		if(IsValid(GetOwner()))
		{
			TObjectPtr<UAbilitySystemComponent> AbilitySystem = GetOwner()->GetComponentByClass<UAbilitySystemComponent>();
			if(AbilitySystem != nullptr)
			{
				AbilitySystem->RemoveLooseGameplayTag(StaggerSettings->StaggerTag);
			}
		}
	}
	if (CurrentStaggerImmunityTime > 0.f)
	{
		CurrentStaggerImmunityTime -= DeltaTime;
		return;
	}

	SetComponentTickEnabled(false);
}
