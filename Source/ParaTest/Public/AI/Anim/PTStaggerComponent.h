// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "PTStaggerComponent.generated.h"

UCLASS(Blueprintable)
class PARATEST_API UPTStaggerSettings : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float StaggerTimeDuration = 2.f;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float StaggerImmunityDuration = 2.f;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FGameplayTag StaggerTag;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PARATEST_API UPTStaggerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPTStaggerComponent();
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(ToolTip="Stagger"))
	TObjectPtr<UPTStaggerSettings> StaggerSettings = nullptr;
	
	UFUNCTION()
	void StartStagger();
	
	bool bStaggered = false;

protected:
	virtual void BeginPlay() override;
	bool CanApplyStagger() const;

	float CurrentStaggerTime = 0.f;
	float CurrentStaggerImmunityTime = 0.f;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
