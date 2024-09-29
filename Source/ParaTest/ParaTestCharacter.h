// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffect.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "ParaTestCharacter.generated.h"


UCLASS(config=Game)
class AParaTestCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AParaTestCharacter();

	/**Ability System**/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAbilitySystemComponent* AbilitySystem = nullptr;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override
	{
		return AbilitySystem;
	}

	UPROPERTY()
	class UPTAttributeSet* AttributeSet = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability System")
	TArray<TSubclassOf<class UGameplayAbility>> CurrentAbilities;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UPTTokenComponent* TokenComponent = nullptr;

	UFUNCTION(BlueprintCallable)
	virtual USkeletalMeshComponent* GetMyMesh() const { return GetMesh(); }

	UFUNCTION(BlueprintNativeEvent)
	void OnDeathStarted(float EffectMagnitude);

	UFUNCTION(BlueprintNativeEvent)
	void OnHit(float EffectMagnitude);

protected:
	virtual void BeginPlay() override;
};
