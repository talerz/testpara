// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/PTEnemyCharacter.h"

#include "AbilitySystemComponent.h"
#include "PTAttributeSet.h"

APTEnemyCharacter::APTEnemyCharacter()
{
	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	// Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh"));
	// Mesh->SetOnlyOwnerSee(true);
	// Mesh->SetupAttachment(RootComponent);
	// Mesh->bCastDynamicShadow = false;
	// Mesh->CastShadow = false;
	// //Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	// Mesh->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystem");
	AttributeSet = CreateDefaultSubobject<UPTAttributeSet>("AttributeSet");
}

void APTEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	if(AbilitySystem)
	{
		AbilitySystem->InitAbilityActorInfo(this, this);
	}
}
