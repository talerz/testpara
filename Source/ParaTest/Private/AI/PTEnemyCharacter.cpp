// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/PTEnemyCharacter.h"

#include "AbilitySystemComponent.h"
#include "AI/Anim/PTStaggerComponent.h"

APTEnemyCharacter::APTEnemyCharacter()
{
	StaggerComponent = CreateDefaultSubobject<UPTStaggerComponent>("StaggerComponent");
}
