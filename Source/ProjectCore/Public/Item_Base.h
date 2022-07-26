// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CoreCharacter.h"
#include "GameFramework/Actor.h"
#include"Engine/DataTable.h"
#include "Player/CorePlayerController.h"
#include "Item_Base.generated.h"


UENUM(BlueprintType)
enum class EItemType : uint8
{
	Weapon = 0                UMETA(DisplayName = "Weapon"),
	Accessory = 1          UMETA(DisplayName = "Accessory"),
	Ammo = 2         UMETA(DisplayName = "Ammo"),
	Health = 3			 UMETA(DisplayName = "Health"),
	Boost = 4			 UMETA(DisplayName = "Boost"),
	Helmet = 5			 UMETA(DisplayName = "Helmet"),
	Vest = 6			     UMETA(DisplayName = "Vest"),
	BackPack = 6			     UMETA(DisplayName = "BackPack"),
	Fashion = 6			     UMETA(DisplayName = "Fashion"),

	
	
};

UENUM(BlueprintType)
enum class EWeaponAccType : uint8
{

	Sight = 0                UMETA(DisplayName = "Sight"),
	Muzzle = 1          UMETA(DisplayName = "Muzzle Weapon"),
	ForeGrip = 2         UMETA(DisplayName = "Foregrip"),
	Mag = 3			 UMETA(DisplayName = "Mag"),
	ButtStoock = 4			 UMETA(DisplayName = "Buttstock"),
	
};

UENUM(BlueprintType)
enum class EWeaponPosition : uint8
{
	Left = 0		UMETA(DisplayName = "Left"),
	Right =1		UMETA(DisplayName = "Right")	
};

// struct for item weapon 

USTRUCT(BlueprintType)
struct FItemWeapon : public FTableRowBase
{

	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ItemWeapon")
		FText Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ItemWeapon")
		UTexture2D* Icon;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ItemWeapon")
		UTexture2D* BigIcon;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ItemWeapon")
		UTexture2D* Thumbnail;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ItemWeapon")
		FName UseAmmoID;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ItemWeapon")
		int ClipSize;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ItemWeapon")
		int Damage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ItemWeapon")
		float FiringInterval;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ItemWeapon")
		float ReplaceClipTime;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ItemWeapon")
		bool bAutoMode;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ItemWeapon")
		UStaticMeshComponent* StaticMesh;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ItemWeapon")
		USkeletalMeshComponent* SkeletalMesh;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ItemWeapon")
		UStaticMeshComponent* DefaultMag;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ItemWeapon")
		UStaticMeshComponent* DefaultSight;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ItemWeapon")
		UStaticMeshComponent* DefaultButtStock;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ItemWeapon")
		USoundBase* FireSound;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ItemWeapon")
		USoundBase* FireSoundSuppressed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ItemWeapon")
		bool bCanSight;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ItemWeapon")
		bool bCanMuzzle;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ItemWeapon")
		bool bCanGrip;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ItemWeapon")
		bool bCanButStock;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ItemWeapon")
		float CrossOffsetMin_Stilness;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ItemWeapon")
		float CrossOffsetMax_Stilness;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ItemWeapon")
		float CrossOffsetMin_Move;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ItemWeapon")
		float CrossOffsetMax_Move;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ItemWeapon")
		float CrossOffsetMin_AimStilness;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ItemWeapon")
		float CrossOffsetMax_AimStilness;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ItemWeapon")
		float CrossOffsetMin_AimMove;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ItemWeapon")
		float CrossOffsetMax_AimMove;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ItemWeapon")
		float VerticleOffset;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ItemWeapon")
		float HorizontalOffset;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ItemWeapon")
		float InitVelocity;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ItemWeapon")
		float Velocity100M;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ItemWeapon")
		float Velocity300M;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ItemWeapon")
		float Velocity500;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ItemWeapon")
		float WalkSpeedPer;


};


USTRUCT(BlueprintType)
struct FItemWeaponAcc : public FTableRowBase
{

	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = " Weapon Accsesories")
	FText Name ;
	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = " Weapon Accsesories")
	EWeaponAccType AccType ;
	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = " Weapon Accsesories")
	FText WeaponIDs ;
	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = " Weapon Accsesories")
	UStaticMeshComponent*WeaponAccMesh ;
	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = " Weapon Accsesories")
	UStaticMeshComponent*WeaponAccMMesh2;
	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = " Weapon Accsesories")
	UTexture2D* Icon ;
	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = " Weapon Accsesories")
	int SightMultiple ;
	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = " Weapon Accsesories")
	bool bIsSupressor ;
	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = " Weapon Accsesories")
	bool bIsNotFlash ;
	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = " Weapon Accsesories")
	float ClipRate ;
	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = " Weapon Accsesories")
	int  ClipCapacity ;
	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = " Weapon Accsesories")
	float VerticleAdjPer ;
	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = " Weapon Accsesories")
	float HorizontalAdjPer;
	
	
};

USTRUCT(BlueprintType)
struct FItemAmmo : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = " Weapon Ammo")
	FText Name ;
	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = " Weapon Ammo")
	UStaticMeshComponent*AmmoMesh ;
	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = " Weapon Ammo")
	int PickupAmmo;
	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = " Weapon Ammo")
	UTexture2D*Icon;
	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = " Weapon Ammo")
	int Weight ;
	
	
};

UCLASS()
class PROJECTCORE_API AItem_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// only used in sub classes thats why protected
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	ACoreCharacter*MyCharacterRef;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	ACorePlayerController*MyControllerRef;

	void Init (EItemType ItemTypee ,FText Namee );

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Item")
	EItemType ItemType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item",meta = (ExposeOnSpawn="true"))
	FName ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item",meta = (ExposeOnSpawn="true"))
	FString SN;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FText Name ;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item",meta = (ExposeOnSpawn="true"))
	int Amount ;

	UFUNCTION(BlueprintCallable)
	int GetWeight ();
	UFUNCTION(BlueprintCallable)
	void UpdateAmount(bool bAdd , bool bReduce , int Amountt );

};
