// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemObjects/Item_Weapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/DataTable.h"

AItem_Weapon::AItem_Weapon()
{


	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	WeaponMesh->SetupAttachment(RootComponent);


	Mag=CreateDefaultSubobject<UStaticMeshComponent>("Mag");
	Mag->SetupAttachment(WeaponMesh);
	Mag->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Muzzle=CreateDefaultSubobject<UStaticMeshComponent>("Muzzle");
	Muzzle->SetupAttachment(WeaponMesh);


	Sight = CreateDefaultSubobject<UStaticMeshComponent>("Sight");
	Sight->SetupAttachment(WeaponMesh);



	ForeGrip = CreateDefaultSubobject<UStaticMeshComponent>("ForeGrip");
	ForeGrip->SetupAttachment(WeaponMesh);

	ButtStock=CreateDefaultSubobject<UStaticMeshComponent>("ButtStock");
	ButtStock->SetupAttachment(WeaponMesh);


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
		}
	}


	

	
	
}


