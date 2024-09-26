// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PTPatrolComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PARATEST_API UPTPatrolComponent : public UActorComponent
{
	GENERATED_BODY()


public:	
	// Sets default values for this component's properties
	UPTPatrolComponent();

	void NewPatrolPointReached(const TObjectPtr<class APTPatrolPoint>& NewPatrolPoint);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//Cached Enemy
	UPROPERTY()
	TObjectPtr<class APTEnemyCharacter> EnemyOwner = nullptr;
	
	UPROPERTY()
	TObjectPtr<class APTAIController> EnemyOwnerController = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol")
	TWeakObjectPtr<class APTPatrolPoint> FirstPatrolPoint = nullptr;
	
private:

	UPROPERTY()
	TObjectPtr<class APTPatrolPoint> CurrentPatrolPoint = nullptr;

		
};
