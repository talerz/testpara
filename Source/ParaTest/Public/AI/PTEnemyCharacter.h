// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ParaTest/ParaTestCharacter.h"
#include "PTEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PARATEST_API APTEnemyCharacter : public AParaTestCharacter
{
	GENERATED_BODY()

public:
	APTEnemyCharacter();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	TObjectPtr<class UPTStaggerComponent> StaggerComponent = nullptr;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AI")
	FGameplayTag StaggerTag;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AI")
	FGameplayAttribute StaggerAttribute;

	UFUNCTION(BlueprintCallable, Category = "Stagger")
	bool IsStaggered() const;
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
