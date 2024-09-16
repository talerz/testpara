// Fill out your copyright notice in the Description page of Project Settings.


#include "ParaTest/Public/PTAttributeSet.h"

#include "GameplayEffectExtension.h"


void UPTAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

		 if (Attribute == GetHealthAttribute())
		 {
			 NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
		 }
}

bool UPTAttributeSet::PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data)
{
	return Super::PreGameplayEffectExecute(Data);
}

void UPTAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
}
