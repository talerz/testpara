// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "PTAttributeSet.generated.h"

// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
/**
 * 
 */
UCLASS()
class PARATEST_API UPTAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual bool PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data) override;

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	UPROPERTY(BlueprintreadOnly, Category = "Health")
	FGameplayAttributeData Health = 50;
	ATTRIBUTE_ACCESSORS(UPTAttributeSet, Health);
	UPROPERTY(BlueprintreadOnly, Category = "Health")
	FGameplayAttributeData MaxHealth = 50;
	ATTRIBUTE_ACCESSORS(UPTAttributeSet, MaxHealth);
	UPROPERTY(BlueprintreadOnly, Category = "Health")
	FGameplayAttributeData Healing =1 ;
	ATTRIBUTE_ACCESSORS(UPTAttributeSet, Healing);
	UPROPERTY(BlueprintreadOnly, Category = "Health")
	FGameplayAttributeData Damage =1 ;

	ATTRIBUTE_ACCESSORS(UPTAttributeSet, Damage);
	
};
