// Copyright Epic Games, Inc. All Rights Reserved.

#include "ParaTestCharacter.h"

#include "AbilitySystemComponent.h"
#include "Animation/AnimInstance.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "PTAttributeSet.h"
#include "Engine/LocalPlayer.h"
#include "Player/PTTokenComponent.h"

class UTP_WeaponComponent;

AParaTestCharacter::AParaTestCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystem");
	AttributeSet = CreateDefaultSubobject<UPTAttributeSet>("AttributeSet");
	TokenComponent = CreateDefaultSubobject<UPTTokenComponent>("TokenComponent");
}

void AParaTestCharacter::OnDeathStarted_Implementation( float EffectMagnitude)
{
	//TODO: Add death anims, FXs
	for (UActorComponent* Component : GetInstanceComponents())
	{
		Component->DestroyComponent();
	}
	Destroy();
}

void AParaTestCharacter::OnHit_Implementation( float EffectMagnitude)
{
	//TODO: Add hit anims	
}

void AParaTestCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	if (AbilitySystem)
	{
		AbilitySystem->InitAbilityActorInfo(this, this);
		for (auto& Ability : CurrentAbilities)
		{
			FGameplayAbilitySpec AbilitySpec = AbilitySystem->BuildAbilitySpecFromClass(Ability);
			AbilitySystem->GiveAbility(AbilitySpec);
		}
	}
}
