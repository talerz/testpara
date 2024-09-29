// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/PTPatrolComponent.h"

#include "AI/PTAIController.h"
#include "AI/PTEnemyCharacter.h"

UPTPatrolComponent::UPTPatrolComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPTPatrolComponent::NewPatrolPointReached(const TObjectPtr<class APTPatrolPoint>& NewPatrolPoint)
{	if (NewPatrolPoint == nullptr)
{
	return;
}
	//No need to setup same patrol point twice
	if (CurrentPatrolPoint == NewPatrolPoint)
	{
		return;
	}
	CurrentPatrolPoint = NewPatrolPoint;

	if (EnemyOwnerController == nullptr)
	{
		return;
	}
	EnemyOwnerController->UpdatePatrolPoint(NewPatrolPoint);
}


void UPTPatrolComponent::BeginPlay()
{
	Super::BeginPlay();
	EnemyOwner = Cast<APTEnemyCharacter>(GetOwner());
	if(EnemyOwner != nullptr)
	{
		EnemyOwnerController = Cast<APTAIController>(EnemyOwner->GetController());
	}
	//Setup start PatrolPoint
	NewPatrolPointReached(FirstPatrolPoint.Get());
}


