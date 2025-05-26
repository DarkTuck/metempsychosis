// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile.generated.h"

UCLASS()
class METEMPSYCHOSIS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY()
	UProjectileMovementComponent* ProjectileMovement;
	UPROPERTY()
	USphereComponent* Collision;
	UPROPERTY()
	UParticleSystemComponent* ParticleSystem;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void OnHit(UPrimitiveComponent* HitComponent, const AActor* OtherActor, UPrimitiveComponent* OtherComp,
	           FVector NormalImpulse,
	           const FHitResult& Hit);
};
