// Copyright Epic Games, Inc. All Rights Reserved.

#include "ParaTestCharacter.h"

#include "AbilitySystemComponent.h"
#include "Animation/AnimInstance.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "PTAttributeSet.h"
#include "Engine/LocalPlayer.h"

class UTP_WeaponComponent;
DEFINE_LOG_CATEGORY(LogTemplateCharacter);

AParaTestCharacter::AParaTestCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	
	AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystem");
	AttributeSet = CreateDefaultSubobject<UPTAttributeSet>("AttributeSet");

}

void AParaTestCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	if(AbilitySystem)
	{
		AbilitySystem->InitAbilityActorInfo(this, this);
	}
	
}
