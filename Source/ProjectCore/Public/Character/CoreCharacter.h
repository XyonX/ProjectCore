// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CharacterAttributeComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/CorePlayerController.h"
#include "AbilitySystemInterface.h"
#include "Item_Base.h"
#include "Abilities/GameplayAbility.h"
#include "Abilities/GameplayAbility.h"
#include "Components/CoreInteractionComponent.h"
#include "CoreCharacter.generated.h"

class UAbilitySystemComponent ;
class USpringArmComponent ;
class UCameraComponent ;
class APlayerController;
class UCharacterAttributeComponent;
class AItem_Weapon;

//DECLARE_DELEGATE_OneParam(OnMoveForwardDelegate, float , Velocity)

UENUM(BlueprintType)
enum class EEquipWeaponPosition : uint8
{
	Hip				UMETA(DisplayName = "Idle Hip"),
	IronSight				UMETA(DisplayName = "Idle Aim"),
	ADS						UMETA(DisplayName = "Ads"),
	
	
};

UCLASS()
class PROJECTCORE_API ACoreCharacter : public ACharacter , public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACoreCharacter();
	
	UFUNCTION(BlueprintNativeEvent)
    void OnGettingDamageFunction(UCharacterAttributeComponent *AttributeComponent,float Healthh,float HealthDelta,const class UDamageType* DamageType,class AController* InstigatedBy,AActor*DamageCauser);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* CharacterMesh;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite , Category = "Camera")
	USpringArmComponent*SpringArm ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite , Category = "Camera")
	USpringArmComponent*SpringArm_ADS ;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	UCameraComponent * Camera ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Character")
	class UCoreInteractionComponent*InteractComponent ;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<AItem_Weapon>PlayerWeapon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	TSubclassOf<UCameraShakeBase>WeaponFireShake;

	


	

 
	
public:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Cammera")
	FVector2D ViewPortSize2D ;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Cammera")
	FVector ViewportLoc_3D ;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Cammera")
	FVector ViewportDir_3D ;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Cammera")
	bool bViewport3D ;

	// LineTrace
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="LineTrace")
	FVector TraceStart_MUZZLE ;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="LineTrace")
	FVector TraceEnd_MUZZLE;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="LineTrace")
	FVector TraceStart_Viewport;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="LineTrace")
	FVector TraceEnd_Viewport;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="LineTrace")
	FVector WeaponAnimDirection;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// declaring values

	//float
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Character")
	float UniversalDeltaTime ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Character",meta = (ToolTip = "this is Idle to walk interp time chooose after trying  multiple value"))
	float IdleToWalkInterpTime ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Character" , meta = (ToolTip = "This is the walk Speed Multipliyer decide how fast character can Walkarround"))
	float WalkSpeedMultiplier ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Character")
	float TurnRate ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Character")
	float LookUpRate ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Character")
	float AdsZoomTime ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Character")
	float FreeLookCameraShiftDelta ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Character")
	float WalkSpeed ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Character")
	float JogSpeed ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Character")
	float SprintSpeed ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Character")
	float DashSpeed ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Character")
	float SlideSpeed ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Character")
	float CrouchSpeed;
	//UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Character")
	//float YawDiff ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Animation")
	float YawOffset_Player;

	//FRotator
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Character")
	FVector FreeLookDirection ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Character")
	FRotator FreeLookCharacterRot;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Socket")
	FName WeaponSocket_Primary;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Socket")
	FName WeaponSocket_Secondary;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Socket")
	FName WeaponSocket_Melee;
	
	


	// declaring bool
	

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Character")
	bool bHasWeaponEquipped;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Character")
	bool bIsMovingRight;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Character")
	bool bWantsToZoom ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Character")
	bool bInADSMode;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Character")
	bool  bWantLearpedMovement ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Character")
	bool  bFreeLookupRotate ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Character")
	bool bInCombatMode ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Character")
	bool bIsSprinting ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Character")
	bool bIsWalking ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Character")
	bool bEnable360AO ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Character")
	bool bIsCrouching ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Character")
	bool bCanSlide;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Character")
	bool bSlideButtonPressed;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Character")
	bool bWalkingForwardBackward;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Character")
	bool bWalkingLeftRight;
	
	


	

	// Declaring Assets Var
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Audio")
	USoundBase*ErrorSound ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Audio")
	USoundBase*FireSound ;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = " Animation Monttage")
	UAnimMontage* FireMontage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = " Animation Monttage")
	UAnimMontage* AM_Idle_Equip_Primary;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = " Animation Monttage")
	UAnimMontage* AM_Equip_Idle_Primary;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = " Animation Monttage")
	UAnimMontage* AM_Idle_Equip_Secondary;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = " Animation Monttage")
	UAnimMontage* AM_Equip_Idle_Secondary;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = " Animation Monttage")
	UAnimMontage*AM_Slide;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = " Animation Monttage")
    UAnimMontage*AM_Turn_L_90;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = " Animation Monttage")
	UAnimMontage*AM_Turn_R_90;

	FName WeaponIDs[3] ;

	EPlayerStatus Playerstatus ;
	// FUNCTIONS 

	UFUNCTION()
	void MoveForward (float Value );
	UFUNCTION()
	void MoveRight (float Value) ;
	UFUNCTION()
	void Turn (float Value) ;
	UFUNCTION()
	void LookUp(float Value);
	UFUNCTION()
	void Interact_Character ();
	
	UFUNCTION(BlueprintCallable)
	void Fire_Core(AItem_Weapon*Weapon);
	UFUNCTION()
	void AutoFire_Start();
	UFUNCTION()
	void AutoFire_Stop();
	UFUNCTION()
	void Fire();// CORE FIRE DOES CALL DIRECTLY BY THE PLAYER
	UFUNCTION()
	void SingleFire();
	UFUNCTION(BlueprintCallable)
	void SpawnWeapon_Primary();
	UFUNCTION(BlueprintCallable)
	void EquipeWeapon_Primary();
	UFUNCTION(BlueprintCallable)
    void EquipeWeapon_Secondary();
	UFUNCTION(BlueprintCallable)
	void SpawnWeapon_Secondary();
    UFUNCTION(BlueprintCallable)
    void EquipeWeapon_Melee();
	UFUNCTION()
	void Ads_Pressed();
	UFUNCTION()
	void Ads_Released();
	void FreeLookup_Pressed();
	void FreeLookup_Released();
	void Sprint_Pressed();
	void Sprint_Released();
	void Crouch_Pressed();
	void Crouch_Released();
	void Crouch_Axis(float Value);
	void Slide();
	void Walk_Pressed ();
	void Walk_Released ();
	void FireLineTrace();


	
	AItem_Weapon* SpawnWeaponFromID(FName IDD) ;
	
	UFUNCTION(BlueprintCallable,Category="Character")
	void AquireAbility(TSubclassOf<UGameplayAbility>AbilityToAquire);
	
	
	

	// Storing Controller Reference 
	UPROPERTY(VisibleAnywhere ,BlueprintReadWrite ,Category = "Character ")
	APlayerController*MyPlayerControlRef ;



	

	// Setting Up Getters
	FORCEINLINE  UCameraComponent* GetCameraComponent () {return Camera; }
	FORCEINLINE  APlayerController * GetPlayerController (){ return MyPlayerControlRef; }
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const ;
	FORCEINLINE UCharacterAttributeComponent* GetCharacterAttributeComp () {return AttributeComp; }


	// DECLARING COMPONENTS 
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Character")
	UCharacterAttributeComponent*AttributeComp;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Character")
	UAbilitySystemComponent*AbilitySystemComp;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	AItem_Weapon* PlayerEquippedWeapon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	AItem_Weapon* Weapon1_Primary;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	AItem_Weapon* Weapon2_Secondary;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	AItem_Weapon* Weapon3_Melee;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	bool bWeaponShouldIdle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	bool bWeaponShouldAim ;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	EEquipWeaponPosition WeaponHoldingPosition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int WaitingTime ;
	FTimerHandle WeaponPositionTimerHandle;
	void SetWeaponPosition();


	UFUNCTION(BlueprintImplementableEvent)
	void OnHealthChangedFunction(AActor* InstigatorActor,UCharacterAttributeComponent*  OwningComp ,  float  NewHealth,float Delta)	;

	


	FORCEINLINE UDataTable* LoadObjFromPath(const FName& Path)
	{
		if (Path == NAME_None) return NULL;

		return Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), NULL, *Path.ToString()));
	}
	

};
