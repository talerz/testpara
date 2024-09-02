// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "PTGameplayAbility_Shoot.generated.h"

/**
 * 
 */
UCLASS()
class PARATEST_API UPTGameplayAbility_Shoot : public UGameplayAbility
{
	GENERATED_BODY()
public:

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	void Shoot();

// protected:
// 	/** Projectile class to spawn */
// 	// UPROPERTY(EditDefaultsOnly, Category=Projectile)
// 	// TSubclassOf<class AParaTestProjectile> ProjectileClass;
// 	//
// 	// /** AnimMontage to play each time we fire */
// 	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
// 	// UAnimMontage* FireAnimation;
//
// 	/** Sound to play each time we fire */
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
// 	USoundBase* FireSound;
// private:
// 	/** The Character holding this weapon*/
// 	AParaTestCharacter* Character;
};
