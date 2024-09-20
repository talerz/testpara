// Fill out your copyright notice in the Description page of Project Settings.


#include "PTGameplayAbility_Shoot.h"

#include "Kismet/GameplayStatics.h"
#include "ParaTest/ParaTestCharacter.h"
#include "ParaTest/ParaTestProjectile.h"
#include "ParaTest/TP_WeaponComponent.h"
#include "Player/PTPlayerCharacter.h"

void UPTGameplayAbility_Shoot::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                               const FGameplayAbilityActorInfo* ActorInfo,
                                               const FGameplayAbilityActivationInfo ActivationInfo,
                                               const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo))
	{
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);
	}
	Shoot();

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}

void UPTGameplayAbility_Shoot::EndAbility(const FGameplayAbilitySpecHandle Handle,
                                          const FGameplayAbilityActorInfo* ActorInfo,
                                          const FGameplayAbilityActivationInfo ActivationInfo,
                                          bool bReplicateEndAbility, bool bWasCancelled)
{
	

	CommitAbilityCooldown(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false);
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UPTGameplayAbility_Shoot::Shoot()
{
	const AParaTestCharacter* Character = Cast<AParaTestCharacter>((GetAvatarActorFromActorInfo()));
	if (Character == nullptr || Character->GetController() == nullptr)
	{
		return;
	}
	const TArray<UActorComponent*> InstComponents = Character->GetInstanceComponents();
	const UTP_WeaponComponent* Weapon = nullptr;
	if (InstComponents.Num() > 0)
	{
		for (auto& InstComponent : InstComponents)
		{
			Weapon = Cast<UTP_WeaponComponent>(InstComponent);
			if (IsValid(Weapon))
			{
				break;
			}
		}
	}
	if (Weapon == nullptr)
	{
		return;
	}

	// Try and fire a projectile
	if (ProjectileClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			FRotator SpawnRotation;

			APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());

			if (IsValid(PlayerController))
			{
				SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
			}
			else
			{
				SpawnRotation = Character->GetActorRotation();
			}
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			const FVector SpawnLocation = Weapon->GetSocketLocation(FName(TEXT("Ammo"))) + SpawnRotation.RotateVector(
				Weapon->MuzzleOffset);

			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride =
				ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			// Spawn the projectile at the muzzle
			World->SpawnActor<AParaTestProjectile>(ProjectileClass, SpawnLocation, SpawnRotation,
			                                       ActorSpawnParams);
		}
	}

	// Try and play the sound if specified
	if (Weapon->FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, Weapon->FireSound, Character->GetActorLocation());
	}

	//Player doesnt use normal mesh, so need to play it on different anim instance
	if (Cast<APTPlayerCharacter>(Character) != nullptr)
	{
		MontageToPlay = nullptr;
		UAnimInstance* AnimInstance = Character->GetMyMesh()->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(MontageToPlay1p, 1.f);
		}
	}
	UAnimInstance* AnimInstance = Character->GetMyMesh()->GetAnimInstance();
	if (AnimInstance != nullptr)
	{
		AnimInstance->Montage_Play(MontageToPlay, 1.f);
	}
}
