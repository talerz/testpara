// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ParaTest/ParaTestCharacter.h"
#include "PTTargetCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PARATEST_API APTTargetCharacter : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()

	APTTargetCharacter();

public:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Character, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MeshComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Character, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxComponent = nullptr;

	/**Ability System**/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAbilitySystemComponent* AbilitySystem = nullptr;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override
	{
		return AbilitySystem;
	}

	UPROPERTY()
	class UPTAttributeSet* AttributeSet = nullptr;
};
