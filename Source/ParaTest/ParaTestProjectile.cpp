// Copyright Epic Games, Inc. All Rights Reserved.

#include "ParaTestProjectile.h"

#include "AbilitySystemComponent.h"
#include "AI/Anim/PTStaggerComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

AParaTestProjectile::AParaTestProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AParaTestProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void AParaTestProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		UAbilitySystemComponent* AbilitySystemComponent = OtherActor->GetComponentByClass<UAbilitySystemComponent>();
		if(AbilitySystemComponent != nullptr)
		{
			//Apply ability effect to the actor that was hit
			AbilitySystemComponent->ApplyGameplayEffectToSelf(HitEffect.GetDefaultObject(), 1.f, AbilitySystemComponent->MakeEffectContext());
		}
		//Start Stagger on Enemies
		TObjectPtr<UPTStaggerComponent> StaggerComponent= OtherActor->GetComponentByClass<UPTStaggerComponent>();
		if(StaggerComponent)
		{
			StaggerComponent->StartStagger();
		}
		Destroy();
	}
}