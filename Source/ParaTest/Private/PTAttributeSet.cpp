// Fill out your copyright notice in the Description page of Project Settings.


#include "ParaTest/Public/PTAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "ParaTest/ParaTestCharacter.h"


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
	
	const bool bDead = GetHealth() <= 0.0f;
	const FGameplayEffectContextHandle& Context = Data.EffectSpec.GetEffectContext();
	AActor* Instigator = Context.GetOriginalInstigator();
	AActor* Causer = Context.GetEffectCauser();
	float Magnitude = FMath::Abs(Data.EvaluatedData.Magnitude);
	
	AParaTestCharacter* Character = Cast<AParaTestCharacter>(Instigator);
	if(!Character)
	{
		return;
	}
	if(bDead)
	{
		Character->OnDeathStarted(Magnitude);
		return;
	}
	Character->OnHit(Magnitude);
}
