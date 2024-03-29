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
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category ="Pickup_Weapon")
	int Ammo ;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="PickupWeapon")
	class UDataTable* WeaponDatTable;
	UFUNCTION(BlueprintCallable)
	void Init_Pickup_Weapon(FName IDD);

	//UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="PickupWeapon")
	//FItemWeapon WeaponItem_Pickup ;
	
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void OnComponentEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	void Interact_Implementation(ACoreCharacter* InstigatorCharacter) override;
	
	FORCEINLINE UDataTable* LoadObjFromPath(const FName& Path)
	{
		if (Path == NAME_None) return NULL;

		return Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), NULL, *Path.ToString()));
	}
	
	
};
