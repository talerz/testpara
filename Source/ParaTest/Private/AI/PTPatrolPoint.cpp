// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/PTPatrolPoint.h"

#include "AI/PTEnemyCharacter.h"
#include "AI/PTPatrolComponent.h"
#include "Components/BillboardComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
APTPatrolPoint::APTPatrolPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bCanEverTick = false;
	
	PatrolCollision = CreateDefaultSubobject<UBoxComponent>("PatrolCollision");
	PatrolCollision->InitBoxExtent(FVector(100.f, 100.f, 100.f));
	PatrolCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	PatrolCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	PatrolCollision->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Overlap);
	RootComponent = PatrolCollision;

	PatrolCollision->OnComponentBeginOverlap.AddDynamic(this, &APTPatrolPoint::OnPatrolPointReached);
	Billboard = CreateDefaultSubobject<UBillboardComponent>("Billboard");
}

void APTPatrolPoint::OnPatrolPointReached(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const TObjectPtr<APTEnemyCharacter> PatrollingEnemy = Cast<APTEnemyCharacter>(OtherActor);
	if(!IsValid(PatrollingEnemy))
	{
		return;
	}
	UPTPatrolComponent* PatrolComponent = PatrollingEnemy->GetComponentByClass<UPTPatrolComponent>();
	if(!IsValid(PatrolComponent))
	{
		return;
	}
	//Set next patrol point 
	PatrolComponent->NewPatrolPointReached(NextPatrolPoint);
}




