// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PTTokenComponent.generated.h"

UENUM()
enum EToken : uint8
{
	Normal,
	Fire,
	Water
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PARATEST_API UPTTokenComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPTTokenComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<TEnumAsByte<EToken>, int32> BaseTokensAmount;
//	UPROPERTY()
//	TMap<TEnumAsByte<EToken>, int32> TokensAmount;
	
	bool TryReserveToken(const TObjectPtr<class APTEnemyCharacter>& AskingCharacter, const EToken Token);

	bool GetToken(const TObjectPtr<class APTEnemyCharacter>& AskingCharacter,const EToken Token);

	void ReturnToken(const TObjectPtr<class APTEnemyCharacter>& AskingCharacter,const EToken Token);

private:
	//Instead of controller, it could have hashed value per token
	TMap<TObjectPtr<class APTEnemyCharacter>, EToken> ReservedTokens;
};
