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
	/** Pawn mesh: 1st person view (arms; seen only by self) */
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Mesh, meta = (AllowPrivateAccess = "true"))
	// USkeletalMeshComponent* Mesh;

	//
	// /**Ability System**/
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	// UAbilitySystemComponent* AbilitySystem;
	//
	// virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override
	// {
	// 	return AbilitySystem;
	// }
	//
	// UPROPERTY()
	// class UPTAttributeSet* AttributeSet;
	//
protected:
	virtual void BeginPlay();

};
