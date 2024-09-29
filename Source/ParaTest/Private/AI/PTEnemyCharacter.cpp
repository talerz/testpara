// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/PTEnemyCharacter.h"

#include "AbilitySystemComponent.h"
#include "AI/Anim/PTStaggerComponent.h"

APTEnemyCharacter::APTEnemyCharacter()
{
	StaggerComponent = CreateDefaultSubobject<UPTStaggerComponent>("StaggerComponent");
}

void APTEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void APTEnemyCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (AbilitySystem != nullptr)
	{
		AbilitySystem->OnAnyGameplayEffectRemovedDelegate().RemoveAll(this);
	}
	Super::EndPlay(EndPlayReason);
	
}

bool APTEnemyCharacter::IsStaggered() const
{
	if(IsValid(StaggerComponent))
	{
		return StaggerComponent->bStaggered;
	}
	return false;
}
