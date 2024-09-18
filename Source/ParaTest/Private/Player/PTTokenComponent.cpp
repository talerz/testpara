// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PTTokenComponent.h"

UPTTokenComponent::UPTTokenComponent()
{
}

bool UPTTokenComponent::TryReserveToken(const EToken Token)
{
	int32 CurrentTokenNumber = BaseTokensAmount.FindRef(Token);
	if (CurrentTokenNumber <= 0)
	{
		//All tokens are taken
		return false;
	}

	CurrentTokenNumber = CurrentTokenNumber - 1;

	BaseTokensAmount.FindOrAdd(Token) = CurrentTokenNumber;
	return true;
}

void UPTTokenComponent::ReturnToken(const EToken Token)
{
	const int32 CurrentTokenNumber = 1 + BaseTokensAmount.FindRef(Token);
	BaseTokensAmount.FindOrAdd(Token) = CurrentTokenNumber;
}
