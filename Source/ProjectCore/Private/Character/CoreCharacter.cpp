// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CoreCharacter.h"
#include "Character/CoreCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include"Components/CoreInteractionComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AbilitySystemComponent.h"
// Sets default values
ACoreCharacter::ACoreCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// creating and setting up spring arm 
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bUsePawnControlRotation=true;

	// Creating And Settingup Camera

	Camera = CreateDefaultSubobject< UCameraComponent>("Camera");

	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;


	bUseControllerRotationPitch = false ;
	bUseControllerRotationRoll = false ;
	bUseControllerRotationYaw = false ;

	GetCharacterMovement()->bOrientRotationToMovement = true ;

	WalkSpeedMultiplier = 1.5f ;
	IdleToWalkInterpTime = 0.5f;
	TurnRate = 1.5f ;
	LookUpRate = 1.5f ;


	// creating Attribute Component For Character
	AttributeComp = CreateDefaultSubobject<UCharacterAttributeComponent>("AttributeComp");

	
	// Creating Ability System Component For Character
	 AbilitySystemComp= CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");


	InteractComponent = CreateDefaultSubobject<UCoreInteractionComponent>("Interact Component");
	PlayerEquippedWeapon = nullptr ;

	bWantLearpedMovement = false ;
}

// Called when the game starts or when spawned
void ACoreCharacter::BeginPlay()
{
	Super::BeginPlay();
	MyPlayerControlRef = UGameplayStatics::GetPlayerController(GetWorld(), 0);
}

// Called every frame
void ACoreCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UniversalDeltaTime = DeltaTime ;

	if ( GetCharacterMovement()->Velocity.Size() >10 && !bIsMovingRight ) 
	{
		FRotator CharacterRot = GetActorRotation();
		FRotator ControlRot = GetControlRotation();
		FRotator NewRot = FRotator(CharacterRot.Pitch,ControlRot.Yaw,CharacterRot.Roll);
		SetActorRotation(NewRot);
	}

}

void ACoreCharacter::MoveForward(float Value)
{

	
	// checking wheathr the controller is available or not 
	if(Controller != nullptr)
	{
		// getting controller rotation and finding the forward vector from control rotation
		FRotator ControlRotation = Controller->GetControlRotation();
		FRotator YawRot(0.0f, ControlRotation.Yaw, 0.f);
		FVector ForwardDirection = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);

		if(bWantLearpedMovement)
		{
			float interpedValue = FMath::FInterpTo(0.0f,Value*WalkSpeedMultiplier,UniversalDeltaTime,IdleToWalkInterpTime);
			AddMovementInput(ForwardDirection, interpedValue);
			
			if(Value*WalkSpeedMultiplier == 0)
			{
			
				float InterpWalkingToIdle = FMath::FInterpTo(Value*WalkSpeedMultiplier,0.0f,UniversalDeltaTime,IdleToWalkInterpTime) ;
				AddMovementInput(ForwardDirection, InterpWalkingToIdle );
			}
		}
		if(bWantLearpedMovement == false)
		{
			AddMovementInput(ForwardDirection,Value);
		}
	
	}
}

void ACoreCharacter::MoveRight(float Value)
{
	// checking wheathr the controller is available or not 
	if(Controller != nullptr)
	{
		// getting controller rotation and finding the forward vector from control rotation
		FRotator ControlRotation = Controller->GetControlRotation();
		FRotator YawRot(0.0f, ControlRotation.Yaw, 0.f);
		FVector RightDirection = FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y);

		if(bWantLearpedMovement)
		{
			float interpedValue = FMath::FInterpTo(0.0f,Value*WalkSpeedMultiplier,UniversalDeltaTime,IdleToWalkInterpTime);
			AddMovementInput(RightDirection, interpedValue);
			bIsMovingRight = true ;
			if(Value*WalkSpeedMultiplier == 0)
			{
			
				float InterpWalkingToIdle = FMath::FInterpTo(Value*WalkSpeedMultiplier,0.0f,UniversalDeltaTime,IdleToWalkInterpTime) ;
				AddMovementInput(RightDirection, InterpWalkingToIdle );
				bIsMovingRight = false ;
			}
		}
		if(bWantLearpedMovement == false )
		{
			AddMovementInput(RightDirection,Value) ;
		}
			
	
	}
}

void ACoreCharacter::Turn(float Value)
{
	if(Controller)
	{
		AddControllerYawInput(Value*TurnRate);
	}
	
}

void ACoreCharacter::LookUp(float Value)

{
	if(Controller)
	{
		AddControllerPitchInput(Value*LookUpRate);
	}
}

void ACoreCharacter::Interact_Character()
{

	if(InteractComponent)
	{
		InteractComponent->Interact_Comp();
	}
	
}

void ACoreCharacter::Fire()
{
}

void ACoreCharacter::AutoFire_Start()
{
}

void ACoreCharacter::AutoFire_Stop()
{
}

void ACoreCharacter::SingleFire()
{
	
}

void ACoreCharacter::EquipeWeapon()
{

	/*
	if(Weapon1_Primary)
	{
		UE_LOG(LogTemp, Warning, TEXT(" weapon1rimary IS Available in Character ") );
		if(PlayerEquippedWeapon == nullptr )
		{
			UE_LOG(LogTemp, Warning, TEXT(" weapon1rimary IS Available && PlayerEquippedWeapon is null   in Character ") );
			PlayerEquippedWeapon = Weapon1_Primary ;
			PlayerEquippedWeapon->SetHidden(false);
			FName SocketName = ("WeaponSocket");
			PlayerEquippedWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), SocketName);
			//PlayerEquippedWeapon->AttachToComponent(CharacterMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, SocketName);
			bHasWeaponEquipped = true;
			
			//PlayerEquippedWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), SocketName);

			return;
		}
		if (PlayerEquippedWeapon)
		{
			UE_LOG(LogTemp, Warning, TEXT(" weapon1rimary  && PlayerEquippedWeapon both Available  in Character ") );
			PlayerEquippedWeapon->Destroy();
			bHasWeaponEquipped = false;
			PlayerEquippedWeapon = nullptr;
			return;
		}
	}*/
	// UDataTable* WeaponDatTable=LoadObjFromPath(TEXT("DataTable'/Game/Datas/DT_Item_Weapon.DT_Item_Weapon'"));


	
	if (PlayerEquippedWeapon == nullptr)
	{
		
		FActorSpawnParameters SpawnParam;
		SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn ;
		//FTransform WeaponSpawnTransForm;
		//FVector WeaponSpawnLocation(0.0f, 0.f, 0.f);
		//FRotator WeaponRotation(0.0f, 0.f, 0.f);
		FVector SpawnLocation = FVector(GetActorLocation().X,GetActorLocation().Y,GetActorLocation().Z+100);
		PlayerEquippedWeapon = GetWorld()->SpawnActor<AItem_Weapon>(AItem_Weapon::StaticClass(),SpawnLocation,GetActorRotation(), SpawnParam);
		PlayerEquippedWeapon->SetID(WeaponIDs[0]);
		ACoreCharacter* WeaponOwner = this;
		PlayerEquippedWeapon->SetOwner(WeaponOwner);
		bHasWeaponEquipped = true;
		FName SocketName = FName ("WeaponSocket");
		PlayerEquippedWeapon->Init_Weapon_Item(WeaponIDs[0]);
		PlayerEquippedWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), SocketName);
		
		return;
	}


	if (PlayerEquippedWeapon)
	{
		PlayerEquippedWeapon->Destroy();
		bHasWeaponEquipped = false;
		PlayerEquippedWeapon = nullptr;
	}

	
}

void ACoreCharacter::Ads_Pressed()
{
}

void ACoreCharacter::Ads_Released()
{
}

void ACoreCharacter::FreeLookup_Pressed()
{

	if(GetMovementComponent()->Velocity.Size()>0)
	{
		bFreeLookupRotate =true ;
	}
	
}

void ACoreCharacter::FreeLookup_Released()
{
	if(GetMovementComponent()->Velocity.Size()>0)
	{
		bFreeLookupRotate = false ;
	}
}

// Called to bind functionality to input
void ACoreCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this,& ACoreCharacter::MoveForward );
	PlayerInputComponent->BindAxis("MoveRight", this, & ACoreCharacter::MoveRight);
	PlayerInputComponent->BindAxis ("Turn" , this , &ACoreCharacter::Turn);
	PlayerInputComponent->BindAxis ("LookUp" , this , &ACoreCharacter::LookUp);
	PlayerInputComponent->BindAction("Jump",IE_Pressed,this , &ACharacter::Jump);
	PlayerInputComponent->BindAction("Interact",IE_Pressed,this,&ACoreCharacter::Interact_Character);

	PlayerInputComponent->BindAction("EquipWeapon",IE_Pressed,this,&ACoreCharacter::EquipeWeapon);
	

	

}

UAbilitySystemComponent* ACoreCharacter::GetAbilitySystemComponent() const
{

	return AbilitySystemComp ;
}

void ACoreCharacter::AquireAbility(TSubclassOf<UGameplayAbility> AbilityToAquire)
{

	if(AbilitySystemComp)
	{
		if(HasAuthority() && AbilityToAquire)
		{
			AbilitySystemComp->GiveAbility(FGameplayAbilitySpec(AbilityToAquire,1,0));
		}
		AbilitySystemComp->InitAbilityActorInfo(this,this);
	}

	
}

/*
ACorePlayerController* ACoreCharacter::GetPlayerController()
{
	PlayerController = GetPlayerController();
	ACorePlayerController* ReturnController = Cast<ACorePlayerController>(PlayerController) ;

	return ReturnController ;
	
	
}*/

