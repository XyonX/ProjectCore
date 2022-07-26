// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupObjects/Pickup_Weapon.h"
#include "Engine/DataTable.h"


APickup_Weapon::APickup_Weapon()
{

	static ConstructorHelpers::FObjectFinder<UDataTable>WeaponDataTableObject(TEXT("DataTable'/Game/Datas/DT_Item_Weapon.DT_Item_Weapon'"));
	if(WeaponDataTableObject.Succeeded())
	{

		WeaponDatTable=WeaponDataTableObject.Object;
	}
	if(WeaponDatTable)
	{
		FItemWeapon*WeaponItem = WeaponDatTable->FindRow<FItemWeapon>(ID,"Context");
		if(WeaponItem)
		{
			FText EQUIP ;
			InitPickup(EItemType::Weapon,WeaponItem->Name,EQUIP,WeaponItem->StaticMesh);
		}
	}
	
	
}
