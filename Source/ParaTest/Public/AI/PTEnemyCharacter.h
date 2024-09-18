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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	float MaxNormalAttackRadius = 400.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	float MaxFireAttackRadius = 600.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	float MinNormalAttackRadius = 200.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	float MinFireAttackRadius = 300.f;
protected:
	virtual void BeginPlay() override;

	

};
