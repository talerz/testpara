// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PTTokenComponent.generated.h"

UENUM(BlueprintType)
enum EToken : uint8
{
	Normal,
	Fire,
	Water
};

UCLASS(Blueprintable)
class PARATEST_API UTokenSettings : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<TEnumAsByte<EToken>, int32> BaseTokensAmount;
	
};
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PARATEST_API UPTTokenComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPTTokenComponent();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UTokenSettings> TokenSettings;
	//TMap<TEnumAsByte<EToken>, int32> BaseTokensAmount;
	UFUNCTION(BlueprintCallable)
	bool TryReserveToken( const EToken Token);
	UFUNCTION(BlueprintCallable)
	void ReturnToken(const EToken Token);
};
