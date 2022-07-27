// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickupObjects/Pickup_Base.h"
#include "ExplosiveBarrel.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCORE_API AExplosiveBarrel : public APickup_Base
{
	GENERATED_BODY()
	AExplosiveBarrel();


public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Obstacle")
	int Damage ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Projectile")
	UParticleSystemComponent*EffectComp;
	
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	
};
