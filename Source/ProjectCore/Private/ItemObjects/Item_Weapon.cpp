// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemObjects/Item_Weapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/DataTable.h"

AItem_Weapon::AItem_Weapon()
{


	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	WeaponMesh->SetupAttachment(RootComponent);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Mag=CreateDefaultSubobject<UStaticMeshComponent>("Mag");
	Mag->SetupAttachment(WeaponMesh);
	//Mag->SetupAttachment(WeaponMesh,MagSocketName);
	Mag->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Muzzle=CreateDefaultSubobject<UStaticMeshComponent>("Muzzle");
	Muzzle->SetupAttachment(WeaponMesh);
	Muzzle->SetCollisionEnabled(ECollisionEnabled::NoCollision);


	Sight = CreateDefaultSubobject<UStaticMeshComponent>("Sight");
	Sight->SetupAttachment(WeaponMesh);
	Sight->SetCollisionEnabled(ECollisionEnabled::NoCollision);



	ForeGrip = CreateDefaultSubobject<UStaticMeshComponent>("ForeGrip");
	ForeGrip->SetupAttachment(WeaponMesh);
	ForeGrip->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	ButtStock=CreateDefaultSubobject<UStaticMeshComponent>("ButtStock");
	ButtStock->SetupAttachment(WeaponMesh);
	ButtStock->SetCollisionEnabled(ECollisionEnabled::NoCollision);


	


	

	
	
}

void AItem_Weapon::BeginPlay()
{
	Super::BeginPlay();
	/*if(ID != NAME_None)
	{
		Init_Weapon_Item(ID);
	}*/


	
}

void AItem_Weapon::Init_Weapon_Item(FName IDD)
{

	

	WeaponDatTable=LoadObjFromPath(TEXT("DataTable'/Game/Datas/DT_Item_Weapon.DT_Item_Weapon'"));
	
	if(WeaponDatTable)
	{

		FItemWeapon*WeaponItem = WeaponDatTable->FindRow<FItemWeapon>(IDD,"Context");

		if(WeaponItem)
		{

			WeaponMesh->SetSkeletalMesh(WeaponItem->SkeletalMesh);
			Mag->SetStaticMesh(WeaponItem->DefaultMag);
			Mag->AttachToComponent(WeaponMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true),MagSocketName);
			Muzzle->AttachToComponent(WeaponMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true),MuzzleSocketName);
			if(WeaponItem->DefaultSight != nullptr)
			{
				Sight->SetStaticMesh(WeaponItem->DefaultSight);
			}
			Sight->AttachToComponent(WeaponMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true),SightSocketName);
			if(WeaponItem->bCanGrip)
			{
				ForeGrip->AttachToComponent(WeaponMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true),ForeGripSocketName);
			}
			if(WeaponItem->DefaultButtStock)
			{
				ButtStock->SetStaticMesh(WeaponItem->DefaultButtStock);
				ButtStock->AttachToComponent(WeaponMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true),ForeGripSocketName);
			}


			//FItemWeapon*WeaponItemData = WeaponDatTable->FindRow<FItemWeapon>(IDD,"Context");
	
			if(WeaponItem->MagSocketName  != NAME_None )
			{
				Mag->AttachToComponent(WeaponMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true),WeaponItem->MagSocketName );

			}
			if(WeaponItem->MuzzleSocketName!= NAME_None )
			{
				Muzzle->AttachToComponent(WeaponMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true),WeaponItem->MuzzleSocketName);
			}

			if(WeaponItem->ForeGripSocketName != NAME_None)
			{
				ForeGrip->AttachToComponent(WeaponMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true),WeaponItem->ForeGripSocketName);
			}
			if(WeaponItem->SightSocketName != NAME_None )
			{
				Sight->AttachToComponent(WeaponMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true),WeaponItem->SightSocketName);
			}
			if(WeaponItem->ButtStockName != NAME_None )
			{
				ButtStock->AttachToComponent(WeaponMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true),WeaponItem->ButtStockName);
			}
			
		}

	
	}

	
}

FItemWeapon* AItem_Weapon::GetWeaponDataFromID(FName IDD)
{
	UDataTable* WeaponTableData =LoadObjFromPath(TEXT("DataTable'/Game/Datas/DT_Item_Weapon.DT_Item_Weapon'"));
	FItemWeapon* WeaponItem = WeaponDatTable->FindRow<FItemWeapon>(IDD,"Context");
	return WeaponItem ;
	
}

FItemWeapon* AItem_Weapon::GetWeaponData()
{
	FItemWeapon* WeaponItem ;
	if(ID != NAME_None)
	{
		UDataTable* WeaponTableData =LoadObjFromPath(TEXT("DataTable'/Game/Datas/DT_Item_Weapon.DT_Item_Weapon'"));
		WeaponItem = WeaponDatTable->FindRow<FItemWeapon>(ID,"Context");

		return WeaponItem;
	}

	else
		
		UDataTable* WeaponTableData =LoadObjFromPath(TEXT("DataTable'/Game/Datas/DT_Item_Weapon.DT_Item_Weapon'"));
		WeaponItem = WeaponDatTable->FindRow<FItemWeapon>(("1"),"Context");
		if(GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Weapon ID Not Available , Weapon Data Requested , Default Data Will be returned !"));
		}
		return WeaponItem;
	
}


