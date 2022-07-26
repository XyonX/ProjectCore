// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CoreCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
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

		float interpedValue = FMath::FInterpTo(0.0f,Value*WalkSpeedMultiplier,UniversalDeltaTime,IdleToWalkInterpTime);
		AddMovementInput(ForwardDirection, interpedValue);
		if(Value*WalkSpeedMultiplier == 0)
		{
			
			float InterpWalkingToIdle = FMath::FInterpTo(Value*WalkSpeedMultiplier,0.0f,UniversalDeltaTime,IdleToWalkInterpTime) ;
			AddMovementInput(ForwardDirection, InterpWalkingToIdle );
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

		float interpedValue = FMath::FInterpTo(0.0f,Value*WalkSpeedMultiplier,UniversalDeltaTime,IdleToWalkInterpTime);
		AddMovementInput(RightDirection, interpedValue);
		if(Value*WalkSpeedMultiplier == 0)
		{
			
			float InterpWalkingToIdle = FMath::FInterpTo(Value*WalkSpeedMultiplier,0.0f,UniversalDeltaTime,IdleToWalkInterpTime) ;
			AddMovementInput(RightDirection, InterpWalkingToIdle );
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

// Called to bind functionality to input
void ACoreCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this,& ACoreCharacter::MoveForward );
	PlayerInputComponent->BindAxis("MoveRight", this, & ACoreCharacter::MoveRight);
	PlayerInputComponent->BindAxis ("Turn" , this , &ACoreCharacter::Turn);
	PlayerInputComponent->BindAxis ("LookUp" , this , &ACoreCharacter::LookUp);
	PlayerInputComponent->BindAction("Jump",IE_Pressed,this , &ACharacter::Jump);

	

	

}

/*
ACorePlayerController* ACoreCharacter::GetPlayerController()
{
	PlayerController = GetPlayerController();
	ACorePlayerController* ReturnController = Cast<ACorePlayerController>(PlayerController) ;

	return ReturnController ;
	
	
}*/

