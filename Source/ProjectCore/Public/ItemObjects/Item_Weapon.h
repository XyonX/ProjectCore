// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item_Base.h"
#include "Item_Weapon.generated.h"


class USkeletalMeshComponent;

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Default		UMETA(DisplayName = " Weapon Type Not Specified"),
	RayCast      UMETA(DisplayName = "Raycast type"),
	Projectile   UMETA(DisplayName = "Projectile Tyepe"),
	Melee     UMETA(DisplayName = "Melee Type"),
	
	
};
UENUM()
enum class EWeaponMode : uint8
{
	SingleFire		UMETA(DisplayName = " Single Shot"),
	AutoFire      UMETA(DisplayName = "Auto Fire "),
	
	
};


UCLASS()
class PROJECTCORE_API AItem_Weapon : public AItem_Base
{
	GENERATED_BODY()
	AItem_Weapon();

public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ItemObject")
	USkeletalMeshComponent*WeaponMesh;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ItemObject")
	UStaticMeshComponent*Mag;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ItemObject")
	UStaticMeshComponent*Muzzle;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ItemObject")
	UStaticMeshComponent*Sight;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ItemObject")
	UStaticMeshComponent*ForeGrip;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ItemObject")
	UStaticMeshComponent*ButtStock;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ItemObject")
	int Ammo ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ItemObject")
	EWeaponPosition WeaponPosition ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ItemObject")
	bool bIsOnHand ;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="PickupWeapon")
	class UDataTable* WeaponDatTable;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="PickupWeapon")
	FName MagSocketName;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="PickupWeapon")
	FName MuzzleSocketName;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="PickupWeapon")
	FName SightSocketName ;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="PickupWeapon")
	FName ForeGripSocketName ;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="PickupWeapon")
	FName ButtStockSocketName;
	
	
	
	
	
};
