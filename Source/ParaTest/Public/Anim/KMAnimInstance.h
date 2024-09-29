// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "Animation/AnimInstance.h"
#include "KMAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PARATEST_API UKMAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:

	virtual void InitializeWithAbilitySystem(TObjectPtr<class UAbilitySystemComponent> AbilitySystem);
	virtual void NativeInitializeAnimation() override;
	
protected:

	// Gameplay tags that can be mapped to blueprint variables. The variables will automatically update as the tags are added or removed.
	// These should be used instead of manually querying for the gameplay tags.
	UPROPERTY(EditDefaultsOnly, Category = "GameplayTags")
	FGameplayTagBlueprintPropertyMap GameplayTagPropertyMap;
	
};
