// Fill out your copyright notice in the Description page of Project Settings.


#include "PTTargetCharacter.h"

#include "AbilitySystemComponent.h"
#include "PTAttributeSet.h"
#include "Components/BoxComponent.h"

APTTargetCharacter::APTTargetCharacter()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComponent->InitBoxExtent(FVector(34.0f, 34.0f, 88.0f));
	
	RootComponent = BoxComponent;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComponent->SetupAttachment(RootComponent);
	
	AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystem");
	AttributeSet = CreateDefaultSubobject<UPTAttributeSet>("AttributeSet");
}

void APTTargetCharacter::BeginPlay()
{
	Super::BeginPlay();
	AbilitySystem->InitAbilityActorInfo(this, this);
}
