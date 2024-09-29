// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim/KMAnimInstance.h"

#include "AbilitySystemGlobals.h"

void UKMAnimInstance::InitializeWithAbilitySystem(TObjectPtr<class UAbilitySystemComponent> AbilitySystem)
{
	check(AbilitySystem);

	GameplayTagPropertyMap.Initialize(this, AbilitySystem);
}

void UKMAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (TObjectPtr<AActor> OwningActor = GetOwningActor())
	{
		if (UAbilitySystemComponent* AbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(OwningActor))
		{
			InitializeWithAbilitySystem(AbilitySystem);
		}
	}
}
