// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PTTokenComponent.h"

// Sets default values for this component's properties
UPTTokenComponent::UPTTokenComponent()
{
	//BaseTokensAmount.Append()
}


// Called when the game starts
void UPTTokenComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


void UPTTokenComponent::ReturnToken(const TObjectPtr<class APTEnemyCharacter>& AskingCharacter, const EToken Token)
{
	if (AskingCharacter == nullptr)
	{
		//Token just to log which one was attepmted to return but Enemy was already dead
		return;
	}
	ReservedTokens.FindAndRemoveChecked(AskingCharacter);

	const int32 CurrentTokenNumber = 1 + BaseTokensAmount.FindRef(Token);
	//CurrentTokenNumber++;
	BaseTokensAmount.FindOrAdd(Token, CurrentTokenNumber);
}

bool UPTTokenComponent::TryReserveToken(const TObjectPtr<class APTEnemyCharacter>& AskingCharacter, const EToken Token)
{
	if (AskingCharacter == nullptr || ReservedTokens.Contains(AskingCharacter))
	{
		//Dont wanna give a ticket to character if it didnt give it back
		return false;
	}

	int32 CurrentTokenNumber = BaseTokensAmount.FindRef(Token);
	if (CurrentTokenNumber <= 0)
	{
		//All tokens are taken
		return false;
	}

	CurrentTokenNumber = CurrentTokenNumber - 1;

	BaseTokensAmount.FindOrAdd(Token) = CurrentTokenNumber;
	ReservedTokens.FindOrAdd(AskingCharacter, Token);
	
	return false;
}

bool UPTTokenComponent::GetToken(const TObjectPtr<class APTEnemyCharacter>& AskingCharacter,const  EToken Token)
{
	return false;
}
