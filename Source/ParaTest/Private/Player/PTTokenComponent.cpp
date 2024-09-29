// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PTTokenComponent.h"

bool UPTTokenComponent::TryReserveToken(const EToken Token)
{
	if(!TokenSettings)
	{
		return false;
	}
	int32 CurrentTokenNumber = TokenSettings->BaseTokensAmount.FindRef(Token);
	if (CurrentTokenNumber <= 0)
	{
		//All tokens are taken
		return false;
	}

	CurrentTokenNumber = CurrentTokenNumber - 1;

	TokenSettings->BaseTokensAmount.FindOrAdd(Token) = CurrentTokenNumber;
	return true;
}

void UPTTokenComponent::ReturnToken(const EToken Token)
{
	if(!TokenSettings)
	{
		return;
	}
	const int32 CurrentTokenNumber = 1 + TokenSettings->BaseTokensAmount.FindRef(Token);
	TokenSettings->BaseTokensAmount.FindOrAdd(Token) = CurrentTokenNumber;
}
