// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickupObjects/Pickup_Base.h"
#include "Pickup_Weapon.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCORE_API APickup_Weapon : public APickup_Base
{
	GENERATED_BODY()
	APickup_Weapon();

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category ="Pickup_Weapon")
	int Ammo ;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="PickupWeapon")
	class UDataTable* WeaponDatTable;
	
	
};
