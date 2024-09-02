// Fill out your copyright notice in the Description page of Project Settings.


#include "ParaTest/Public/PTAttributeSet.h"

#include "GameplayEffectExtension.h"

void UPTAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
}

bool UPTAttributeSet::PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data)
{
	return Super::PreGameplayEffectExecute(Data);
}

void UPTAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	//Getting Damage
	if(Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		if(GetDamage() > 0.f)
		{
			const float CurrentHP = FMath::Clamp(GetHealth() - GetDamage(), 0.f, GetMaxHealth());
			
		}
	}
	//Getting Healing
	if(Data.EvaluatedData.Attribute == GetHealingAttribute())
	{
		if(GetHealing() > 0.f)
		{
			const float CurrentHP = FMath::Clamp(GetHealth() + GetDamage(), 0.f, GetMaxHealth());
		}
	}
	
}
