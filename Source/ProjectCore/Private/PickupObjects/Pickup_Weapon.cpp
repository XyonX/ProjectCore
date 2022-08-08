// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupObjects/Pickup_Weapon.h"
#include "Engine/DataTable.h"


APickup_Weapon::APickup_Weapon()
{
	
	
}

void APickup_Weapon::BeginPlay()
{

	Super::BeginPlay();
	
}

void APickup_Weapon::Init_Pickup_Weapon(FName IDD)
{
	//WeaponDatTable = LoadObjFromPath<UDataTable>(TEXT("DataTable'/Game/Datas/DT_Item_Weapon.DT_Item_Weapon'"));
	WeaponDatTable = LoadObjFromPath(TEXT("DataTable'/Game/Datas/DT_Item_Weapon.DT_Item_Weapon'"));

	//static ConstructorHelpers::FObjectFinder<UDataTable>WeaponDataTableObject(TEXT("'/Game/Datas/DT_Item_Weapon.DT_Item_Weapon'"));
	
	
	
	//static ConstructorHelpers::FObjectFinder<UDataTable>WeaponDataTableObject(TEXT("DataTable'/Game/Datas/DT_Item_Weapon.DT_Item_Weapon'"));
	
	if(WeaponDatTable)
	
	{

			UE_LOG(LogTemp, Warning, TEXT("Data Table Found") );
			TArray<FName> RowNames = WeaponDatTable->GetRowNames();
			FItemWeapon*WeaponItem = WeaponDatTable->FindRow<FItemWeapon>(IDD,"Context");
			if(WeaponItem)
			{
				FText EQUIP ;
				InitPickup(EItemType::Weapon,WeaponItem->Name,EQUIP,WeaponItem->StaticMesh);
			}
		
	}
	
}
