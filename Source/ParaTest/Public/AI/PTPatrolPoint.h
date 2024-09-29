// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PTPatrolPoint.generated.h"

UCLASS()
class PARATEST_API APTPatrolPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APTPatrolPoint();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Patrol")
	TObjectPtr<APTPatrolPoint> NextPatrolPoint = nullptr;

protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UBillboardComponent> Billboard = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UBoxComponent> PatrolCollision = nullptr;

	UFUNCTION()
	void OnPatrolPointReached(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
