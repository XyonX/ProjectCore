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
#include"Camera/CameraShakeBase.h"
#include "Components/HealthComponent.h"
#include "Engine/World.h"
#include "Kismet/KismetMaterialLibrary.h"
#include"Components/CharacterAttributeComponent.h"
#include"Kismet/KismetMathLibrary.h"
#include "ItemObjects/Item_Weapon.h"
#include "Particles/ParticleSystem.h"
// Sets default values
ACoreCharacter::ACoreCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// creating and setting up spring arm 
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bUsePawnControlRotation=true;
	// creating and setting up spring arm  ADS
	
	SpringArm_ADS = CreateDefaultSubobject<USpringArmComponent>("SpringArm_ADS");
	SpringArm_ADS->SetupAttachment(RootComponent);
	SpringArm_ADS->bUsePawnControlRotation=true;

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
	FreeLookCameraShiftDelta = 5.0f ;
	bInCombatMode = false;
	AdsZoomTime = 2.0f;
	bIsWalking =false;
	bIsSprinting =false;

	bInCombatMode = false;

	WalkSpeed = 200.0f;
	JogSpeed=200.0f;
	SprintSpeed = 600.0f;
	GetCharacterMovement()->MaxWalkSpeed = JogSpeed ;
	WaitingTime=10;
	bWeaponShouldIdle=false;
	bCanSlide=false;
	WeaponHoldingPosition=EEquipWeaponPosition::IronSight;
}

void ACoreCharacter::OnGettingDamageFunction_Implementation(UCharacterAttributeComponent* AttributeComponent,
	float Healthh, float HealthDelta, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	GEngine->AddOnScreenDebugMessage(-8, 5.f, FColor::White, TEXT("On getting Damage Event Functiion Called"));
	
}

// Called when the game starts or when spawned
void ACoreCharacter::BeginPlay()
{
	Super::BeginPlay();
	MyPlayerControlRef = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	//AttributeComp->OnGettingDamage.AddDynamic(	this,&ACoreCharacter::OnGettingDamageFunction);
	AttributeComp->OnHealthChangeAtrriBute.AddDynamic(this,&ACoreCharacter::OnHealthChangedFunction);
}

// Called every frame
void ACoreCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UniversalDeltaTime = DeltaTime ;

	if ( GetCharacterMovement()->Velocity.Size() >10 && !bIsMovingRight && bFreeLookupRotate == false ) 
	{
		FRotator CharacterRot = GetActorRotation();
		FRotator ControlRot = GetControlRotation();
		FRotator NewRot = FRotator(CharacterRot.Pitch,ControlRot.Yaw,CharacterRot.Roll);
		SetActorRotation(NewRot);
	}
	if(bFreeLookupRotate == false )
	{
		FRotator LastControlRot = GetControlRotation();
		FreeLookDirection = FRotationMatrix(LastControlRot).GetUnitAxis(EAxis::X);
		FreeLookCharacterRot = GetActorRotation();
	}

	if(bEnable360AO)
	{


		float YawDiff =0.0f ;
		
		float MyControlRotYaw = MyPlayerControlRef->GetControlRotation().Yaw ;
		FRotator MyActorRot = GetActorRotation() ;
		float MyActorRotYaw = GetActorRotation().Yaw;
		

		if(GetActorRotation().Yaw <0)
		{
			MyActorRotYaw = 360+GetActorRotation().Yaw ; 
		}
		if(GetActorRotation().Yaw > 0)
		{
			MyActorRotYaw =  FMath::Clamp(GetActorRotation().Yaw,0,180)  ;
		}



		

		if(MyControlRotYaw-MyActorRotYaw>90)
		{
			FRotator NewRot(0 , 0,MyControlRotYaw);
			SetActorRotation(  NewRot);
		}
		if(MyControlRotYaw-MyActorRotYaw < -90)
		{
			FRotator NewRot(0 , 0,MyControlRotYaw);
			SetActorRotation(  NewRot);
		}
			
	}

	/*
	if(bIsWalking)
	{
		GetCharacterMovement()->MaxWalkSpeed=WalkSpeed;
		
	}
	if(bIsSprinting)
	{
		GetCharacterMovement()->MaxWalkSpeed=SprintSpeed;
	}
	if(bIsWalking && bIsSprinting)
	{
		GetCharacterMovement()->MaxWalkSpeed=SprintSpeed;
	}
	else
		GetCharacterMovement()->MaxWalkSpeed = JogSpeed ;
		*/
	if(bIsSprinting )
	{
		if(bIsSprinting && GetCharacterMovement()->Velocity.Size()>0 )
		{
			Playerstatus = EPlayerStatus::Sprinting_Gen ;
		}
		if(bIsSprinting && bIsCrouching)
		{
			bCanSlide=true;
		}
	}
	if(bIsWalking )
	{
		if(bIsSprinting)
		{
			Playerstatus = EPlayerStatus::Sprinting_Gen ;
		}
		if(bIsCrouching)
		{
			Playerstatus=EPlayerStatus::Crouching_Gen;
			
		}
		else
			Playerstatus =EPlayerStatus::Walking_Gen ;
	}
	if( bIsSprinting == false && bIsCrouching)
	{
		Playerstatus=EPlayerStatus::Crouching_Gen;
	}
	if(bIsWalking == false && bIsSprinting == false )
	{
		Playerstatus = EPlayerStatus::Idle ;
	}


	if(bWeaponShouldIdle)
	{
		WeaponHoldingPosition=EEquipWeaponPosition::Hip;
	}
	
	switch (Playerstatus)
	{
	case EPlayerStatus::Walking_Gen :
		{
			//float InterpWalkSpeed = FMath::FInterpTo(0.0f,DefWalkingSpeed,UniversalDeltaTime,IdleToWalkInterpTime);
			GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
			UE_LOG(LogTemp, Warning, TEXT("Walking "));
			break;
		}
		
	case EPlayerStatus::Sprinting_Gen :
		{
			//float InterpSprintSpeed  = FMath::FInterpTo(DefWalkingSpeed,DefSprintSpeed,UniversalDeltaTime,WalkToSprintInterpTime);
			GetCharacterMovement()->MaxWalkSpeed  = SprintSpeed ;
			UE_LOG(LogTemp, Warning, TEXT("Sprinting"));
			break;
		}
	case  EPlayerStatus::Crouching_Gen :
		{
			GetCharacterMovement()->MaxWalkSpeed=CrouchSpeed;
			UE_LOG(LogTemp, Warning, TEXT("Crouching"));
			break;
			
		}
		
		
/*	case EPlayerStatus::Jog_Gen :
		{
			//float InterpCrouchSpeed = FMath::FInterpTo(DefWalkingSpeed,DefCrouchSpeed,UniversalDeltaTime,WalkToCrouchInterpTime) ;
			GetCharacterMovement()->MaxWalkSpeed =DefCrouchSpeed ;
			UE_LOG(LogTemp, Warning, TEXT("Crouching"));
			break;
		}*/
	default:
		GetCharacterMovement()->MaxWalkSpeed = JogSpeed;

		
	}
	if (GetCharacterMovement()->Velocity.X == 0)
	{
		Playerstatus = EPlayerStatus::Idle;
	}

	/*
	if(GetMovementComponent()->Velocity.Size()==0)
	{
		if(YawOffset_Player==-90)
		{
			if(AM_Turn_L_90)
			{
				PlayAnimMontage(AM_Turn_L_90);
			}
			
		}
		if(YawOffset_Player==90)
		{
			if(AM_Turn_R_90)
			{
				PlayAnimMontage(AM_Turn_R_90);
			}
			
		}
	}*/

}

void ACoreCharacter::MoveForward(float Value)
{
	if(Value !=0)
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
			if(bWantLearpedMovement == false )
			{
				//FVector ForwardDire_FreeLook ;
				if(bFreeLookupRotate == false)
				{
					UE_LOG(LogTemp, Warning, TEXT("Moving Without Freelook") );
					AddMovementInput(ForwardDirection,Value);
				
				}
			
				if(bFreeLookupRotate)
				{
					UE_LOG(LogTemp, Warning, TEXT("Free look Mode Activated") );
					//UE_LOG(LogTemp, Warning, TEXT("Text, %d %f %s"), intVar, floatVar, *fstringVar );
					AddMovementInput(FreeLookDirection,Value);
				}
			}
			bWalkingForwardBackward=true;
	
		}
	}
	if(Value==0)
	{
		bWalkingForwardBackward=false;
	}
}

void ACoreCharacter::MoveRight(float Value)
{
	if(Value!=0)
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
			bWalkingLeftRight=true;
	
		}
	}
	if(Value==0)
	{
		bWalkingLeftRight=false;
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

void ACoreCharacter::Fire_Core(AItem_Weapon*Weapon)
{
	if (bHasWeaponEquipped && PlayerEquippedWeapon)
	{
		bWeaponShouldIdle =false;
		EWeaponType WeaponType = PlayerEquippedWeapon->GetWeaponData()->WeaponType;
		GetWorld()->GetTimerManager().SetTimer(WeaponPositionTimerHandle,this,&ACoreCharacter::SetWeaponPosition,10.0,false);

		switch (WeaponType)
		{

		case EWeaponType::Melee :
			UE_LOG(LogTemp,Warning,TEXT("Weapon Type  Melee "))
			if (PlayerEquippedWeapon->GetWeaponData()->FireMontage)
			{
				PlayAnimMontage(PlayerEquippedWeapon->GetWeaponData()->FireMontage, 1.0f);
			}
			if (PlayerEquippedWeapon->GetWeaponData()->MuzzleFlash )
			{
		
				UGameplayStatics::SpawnEmitterAttached(PlayerEquippedWeapon->GetWeaponData()->MuzzleFlash, PlayerEquippedWeapon->WeaponMesh, PlayerEquippedWeapon->GetWeaponData()->MuzzleSocketName);
			}
			if (PlayerEquippedWeapon->GetWeaponData()->FireSound)
			{
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), PlayerEquippedWeapon->GetWeaponData()->FireSound,PlayerEquippedWeapon->GetActorLocation());
			}
			break;
			
		case EWeaponType::RayCast:
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Ray Cast Fired!"));

			FireLineTrace();
			UE_LOG(LogTemp,Warning,TEXT("Weapon Type  Raycast "))
			if (PlayerEquippedWeapon->GetWeaponData()->FireMontage)
			{
				PlayAnimMontage(PlayerEquippedWeapon->GetWeaponData()->FireMontage, 1.0f);
			}
			if (PlayerEquippedWeapon->GetWeaponData()->MuzzleFlash )
			{
		
				UGameplayStatics::SpawnEmitterAttached(PlayerEquippedWeapon->GetWeaponData()->MuzzleFlash, PlayerEquippedWeapon->WeaponMesh, PlayerEquippedWeapon->GetWeaponData()->MuzzleSocketName);
			}
			if (PlayerEquippedWeapon->GetWeaponData()->FireSound)
			{
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), PlayerEquippedWeapon->GetWeaponData()->FireSound,PlayerEquippedWeapon->GetActorLocation());
			}

			// CHECKING IF Viewport available or not
			
			if(GEngine && GEngine->GameViewport)
			{
				GEngine->GameViewport->GetViewportSize(ViewPortSize2D);
			}
			APlayerController* Pc = Cast<APlayerController>(GetController());

			if (Pc)
			{
				if(PlayerEquippedWeapon->GetWeaponData()->FireCameraShake)
				{
					Pc->ClientStartCameraShake(PlayerEquippedWeapon->GetWeaponData()->FireCameraShake);
				}
			}


			
		
		}
	}
}
void ACoreCharacter::FireLineTrace()
{
	
		// cross hair loc 2D
			FVector2D CrossHairLoc(ViewPortSize2D.X/2,ViewPortSize2D.Y/2);

			// Projecting the 2d onto 3d
			bViewport3D = UGameplayStatics::DeprojectScreenToWorld(UGameplayStatics::GetPlayerController(this,0),CrossHairLoc,ViewportLoc_3D,ViewportDir_3D);
			// line tracing

			FHitResult BulletHit;
			FHitResult BulletHit_ViewPort;
			FCollisionQueryParams QuerryParam;
			FCollisionQueryParams QuerryParam_ViewPort;
			QuerryParam_ViewPort.AddIgnoredActor(this);
			QuerryParam_ViewPort.AddIgnoredActor(PlayerEquippedWeapon);
			QuerryParam.AddIgnoredActor(this);
			QuerryParam.AddIgnoredActor(PlayerEquippedWeapon);
			QuerryParam.bTraceComplex = true;
			QuerryParam.bReturnPhysicalMaterial = true;

						
				// line tracing from muzzle 
		
			TraceStart_MUZZLE = PlayerEquippedWeapon->WeaponMesh->GetSocketLocation(PlayerEquippedWeapon->GetWeaponData()->MuzzleSocketName);//PlayerEquippedWeapon->GetMuzzleSocketTransform().GetLocation();
			FRotator Rotation = PlayerEquippedWeapon->WeaponMesh->GetSocketRotation(PlayerEquippedWeapon->GetWeaponData()->MuzzleSocketName);
			//FVector RotationAxis = Rotation.GetAxisX();
			FVector ShootDirection_MUZZLE = Rotation.Vector();
			TraceEnd_MUZZLE = TraceStart_MUZZLE + (ShootDirection_MUZZLE * PlayerEquippedWeapon->GetWeaponData()->WeaponRange);

			
			// line trace from viewpoint
	
			//GetActorEyesViewPoint(EyeLoc, EyeRot);
			
			TraceStart_Viewport =  ViewportLoc_3D ;
			
			FVector ShootDirection =ViewportDir_3D;
			
			TraceEnd_Viewport = TraceStart_Viewport + (ShootDirection * PlayerEquippedWeapon->GetWeaponData()->WeaponRange);

	
	
			if (GetWorld()->LineTraceSingleByChannel(BulletHit, TraceStart_MUZZLE, TraceEnd_Viewport,ECC_Visibility, QuerryParam))
				
			{
				
					
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Line Trace done from  Muzzle to viewport end !"));
					AActor* HitActor = BulletHit.GetActor();
					DrawDebugLine(GetWorld(), TraceStart_MUZZLE, TraceEnd_Viewport, FColor::Blue, false, 2.0f);
					DrawDebugLine(GetWorld(), TraceStart_Viewport, TraceEnd_Viewport, FColor::Blue, false, 2.0f);
					DrawDebugPoint(GetWorld(), BulletHit.Location, 5.f, FColor::Red, false, 2.f);
			
					//UPhysicalMaterial HitMaterial = BulletHit.PhysMaterial;
			
					//EPhysicalSurface HitSurface = UPhysicalMaterial::DetermineSurfaceType(BulletHit.PhysMaterial.Get());
				
					
				
					
					if(HitActor)
					{
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("HIT ACTOR AVAILABLE"));
						WeaponAnimDirection =  UKismetMathLibrary::GetDirectionUnitVector(TraceStart_MUZZLE,HitActor->GetActorLocation());
						UE_LOG(LogTemp, Warning, TEXT("Hit Actor Name %s"),*HitActor->GetName());
						UCharacterAttributeComponent*HitActorAttribute =  Cast<UCharacterAttributeComponent>(HitActor->GetComponentByClass(UCharacterAttributeComponent::StaticClass()));
						if(HitActorAttribute)
						{
							float Damage = PlayerEquippedWeapon->GetWeaponData()->Damage;
							HitActorAttribute->ApplyHealthChange(50);
								//HitActorAttribute->OnHealthChangeAtrriBute.Broadcast();
							
						}
					}
					/*switch (HitSurface)
					{
					case SurfaceType1:
		
					case SurfaceType2:
						TracedParticleEffect = PlayerEquippedWeapon->ImpactParticle_Critical;
							break;
					case SurfaceType3:
						TracedParticleEffect = PlayerEquippedWeapon->ImpactParticle_Wood;
						break;
					case SurfaceType4:
						TracedParticleEffect = PlayerEquippedWeapon->ImpactParticle_Concrete;
						break;
					case SurfaceType5:
						TracedParticleEffect = PlayerEquippedWeapon->ImpactParticle_Metal;
						break;
					default:
						TracedParticleEffect = PlayerEquippedWeapon->ImpactParticle;
						break;
					}*/

					UParticleSystem*TracedParticleEffect=PlayerEquippedWeapon->GetWeaponData()->ImpactParticle;
					if (TracedParticleEffect && BulletHit.bBlockingHit)
					{
						UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TracedParticleEffect, BulletHit.Location);
					}


			}
				
			
}
	

void ACoreCharacter::Fire()
{
/*
	if(bHasWeaponEquipped == false)
	{
		bInCombatMode = true ;
	}*/

	if(bHasWeaponEquipped == false  )
	{
		
		if( WeaponIDs[0] != NAME_None || WeaponIDs[1] != NAME_None || WeaponIDs[2] != NAME_None  )
		{
			EquipeWeapon_Primary();
			
			//Fire_Core(PlayerEquippedWeapon) ;
		}
		if(ErrorSound)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), ErrorSound, 1.0f);
		}
		
		
	}
	if(bHasWeaponEquipped)
	{

		Fire_Core(PlayerEquippedWeapon) ;
		bInCombatMode = true ;
		
	}
	

	
	
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

void ACoreCharacter::SpawnWeapon_Primary()
{

	if(WeaponIDs[1] != NAME_None)
	{
		
			FActorSpawnParameters SpawnParam;
			SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn ;
			//FTransform WeaponSpawnTransForm;
			//FVector WeaponSpawnLocation(0.0f, 0.f, 0.f);
			//FRotator WeaponRotation(0.0f, 0.f, 0.f);
			FVector SpawnLocation = FVector(GetActorLocation().X,GetActorLocation().Y,GetActorLocation().Z+100);
			Weapon1_Primary = GetWorld()->SpawnActor<AItem_Weapon>(AItem_Weapon::StaticClass(),SpawnLocation,GetActorRotation(), SpawnParam);
			//PlayerEquippedWeapon = Weapon1_Primary ;
			Weapon1_Primary->SetID(WeaponIDs[1]);
			ACoreCharacter* WeaponOwner = this;
			Weapon1_Primary->SetOwner(WeaponOwner);
			//bHasWeaponEquipped = true;
			//FName SocketName = PlayerEquippedWeapon->CharacterSocket;
			Weapon1_Primary->Init_Weapon_Item(WeaponIDs[1]);
			Weapon1_Primary->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), WeaponSocket_Primary);
	}

	
}

void ACoreCharacter::EquipeWeapon_Primary()
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
				
				if(Weapon1_Primary == nullptr)
				{
					bWeaponShouldIdle=false;
					GetWorld()->GetTimerManager().SetTimer(WeaponPositionTimerHandle,this,&ACoreCharacter::SetWeaponPosition,10.0,false);

					
					if(WeaponIDs[1] != NAME_None)
					{
						FActorSpawnParameters SpawnParam;
						SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn ;
						//FTransform WeaponSpawnTransForm;
						//FVector WeaponSpawnLocation(0.0f, 0.f, 0.f);
						//FRotator WeaponRotation(0.0f, 0.f, 0.f);
						FVector SpawnLocation = FVector(GetActorLocation().X,GetActorLocation().Y,GetActorLocation().Z+100);
						Weapon1_Primary = GetWorld()->SpawnActor<AItem_Weapon>(AItem_Weapon::StaticClass(),SpawnLocation,GetActorRotation(), SpawnParam);
						//PlayerEquippedWeapon = Weapon1_Primary ;
						Weapon1_Primary->SetID(WeaponIDs[1]);
						ACoreCharacter* WeaponOwner = this;
						Weapon1_Primary->SetOwner(WeaponOwner);
						bHasWeaponEquipped = true;
						//FName SocketName = PlayerEquippedWeapon->CharacterSocket;
						Weapon1_Primary->Init_Weapon_Item(WeaponIDs[1]);
						if(AM_Idle_Equip_Primary)
						{
							PlayAnimMontage(AM_Equip_Idle_Primary,1.0f);
						}
						Weapon1_Primary->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), PlayerEquippedWeapon->CharacterSocket);
						PlayerEquippedWeapon = Weapon1_Primary ;
						
					}
					return;
				}
				if(Weapon1_Primary)
				{
					if(AM_Idle_Equip_Primary)
					{
						PlayAnimMontage(AM_Equip_Idle_Primary,1.0f);
					}
					Weapon1_Primary->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), Weapon1_Primary->CharacterSocket);
					PlayerEquippedWeapon = Weapon1_Primary ;
					bHasWeaponEquipped =true;
					
					return;
				}
				
			}
	


			if (PlayerEquippedWeapon)
			{

				
				PlayerEquippedWeapon->Destroy();
				bHasWeaponEquipped = false;
				PlayerEquippedWeapon = nullptr;
				PlayAnimMontage(AM_Equip_Idle_Primary,1.0f);
				Weapon1_Primary->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), WeaponSocket_Primary);
			}
	}

void ACoreCharacter::SpawnWeapon_Secondary()
{
	if(WeaponIDs[2] != NAME_None)
	{
			FActorSpawnParameters SpawnParam;
			SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn ;
			//FTransform WeaponSpawnTransForm;
			//FVector WeaponSpawnLocation(0.0f, 0.f, 0.f);
			//FRotator WeaponRotation(0.0f, 0.f, 0.f);
			FVector SpawnLocation = FVector(GetActorLocation().X,GetActorLocation().Y,GetActorLocation().Z+100);
			Weapon2_Secondary = GetWorld()->SpawnActor<AItem_Weapon>(AItem_Weapon::StaticClass(),SpawnLocation,GetActorRotation(), SpawnParam);
			//PlayerEquippedWeapon = Weapon1_Primary ;
			Weapon2_Secondary->SetID(WeaponIDs[1]);
			ACoreCharacter* WeaponOwner = this;
			Weapon2_Secondary->SetOwner(WeaponOwner);
			bHasWeaponEquipped = true;
			//FName SocketName = PlayerEquippedWeapon->CharacterSocket;
			Weapon2_Secondary->Init_Weapon_Item(WeaponIDs[1]);
			Weapon2_Secondary->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), WeaponSocket_Secondary);
		
	}
	
}

void ACoreCharacter::EquipeWeapon_Secondary()
{

	if(WeaponIDs[2] != NAME_None)
	{
		if (PlayerEquippedWeapon == nullptr)
		{
		
			if(Weapon2_Secondary == nullptr)
			{
				FActorSpawnParameters SpawnParam;
				SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn ;
				//FTransform WeaponSpawnTransForm;
				//FVector WeaponSpawnLocation(0.0f, 0.f, 0.f);
				//FRotator WeaponRotation(0.0f, 0.f, 0.f);
				FVector SpawnLocation = FVector(GetActorLocation().X,GetActorLocation().Y,GetActorLocation().Z+100);
				Weapon2_Secondary = GetWorld()->SpawnActor<AItem_Weapon>(AItem_Weapon::StaticClass(),SpawnLocation,GetActorRotation(), SpawnParam);
				//PlayerEquippedWeapon = Weapon1_Primary ;
				Weapon2_Secondary->SetID(WeaponIDs[1]);
				ACoreCharacter* WeaponOwner = this;
				Weapon2_Secondary->SetOwner(WeaponOwner);
				bHasWeaponEquipped = true;
				//FName SocketName = PlayerEquippedWeapon->CharacterSocket;
				Weapon2_Secondary->Init_Weapon_Item(WeaponIDs[1]);
				Weapon2_Secondary->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), PlayerEquippedWeapon->CharacterSocket);
				PlayerEquippedWeapon = Weapon2_Secondary ;
				return;
			}
			if(Weapon2_Secondary)
			{
				Weapon1_Primary->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), PlayerEquippedWeapon->CharacterSocket);
				PlayerEquippedWeapon =Weapon2_Secondary ;
				return;
			}
		}
	


		if (PlayerEquippedWeapon)
		{
			PlayerEquippedWeapon->Destroy();
			bHasWeaponEquipped = false;
			PlayerEquippedWeapon = nullptr;
		}
	}

	
}

void ACoreCharacter::EquipeWeapon_Melee()
{

	if(WeaponIDs[0] != NAME_None)
	{
		if (PlayerEquippedWeapon == nullptr)
		{
		
			FActorSpawnParameters SpawnParam;
			SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn ;
			//FTransform WeaponSpawnTransForm;
			//FVector WeaponSpawnLocation(0.0f, 0.f, 0.f);
			//FRotator WeaponRotation(0.0f, 0.f, 0.f);
			FVector SpawnLocation = FVector(GetActorLocation().X,GetActorLocation().Y,GetActorLocation().Z+100);
			Weapon2_Secondary = GetWorld()->SpawnActor<AItem_Weapon>(AItem_Weapon::StaticClass(),SpawnLocation,GetActorRotation(), SpawnParam);
			PlayerEquippedWeapon = Weapon2_Secondary ;
			PlayerEquippedWeapon->SetID(WeaponIDs[0]);
			ACoreCharacter* WeaponOwner = this;
			PlayerEquippedWeapon->SetOwner(WeaponOwner);
			bHasWeaponEquipped = true;
			FName SocketName = PlayerEquippedWeapon->GetWeaponData()->CharacterStockName;
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

	
}

void ACoreCharacter::Ads_Pressed()
{
	bWeaponShouldAim = false;
	bWeaponShouldIdle =false;
	bWantsToZoom = true ;
	bInADSMode=true;
	Camera->AttachToComponent(SpringArm_ADS, FAttachmentTransformRules::KeepRelativeTransform,NAME_None);
	FVector RelativeLcoation(0.0f,0.0f,0.0f);
	FRotator RelativeRotation (0.0f,0.0f,0.0f);
	FLatentActionInfo LatentInfo ;
	UKismetSystemLibrary::MoveComponentTo(Camera,RelativeLcoation,RelativeRotation,true,true,AdsZoomTime,false,EMoveComponentAction::Move, LatentInfo);
}

void ACoreCharacter::Ads_Released()
{
	bWantsToZoom = false;
	bWeaponShouldAim = true;
	bInADSMode=false;

	Camera->AttachToComponent(SpringArm, FAttachmentTransformRules::KeepRelativeTransform,NAME_None);
	FVector TargetLoc (0,0,0);
	FRotator TargetRot(0,0,0);
	FLatentActionInfo LatentInfo;
	//LatentInfo.CallbackTarget = this;
	UKismetSystemLibrary::MoveComponentTo(Camera,TargetLoc,TargetRot,true,true,AdsZoomTime,false,EMoveComponentAction::Move,LatentInfo);
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
	
	bFreeLookupRotate = false ;	
	/*FRotator ControlRot = GetControlRotation();
	float YawChange = FMath::FInterpTo(ControlRot.Yaw, FreeLookCharacterRot.Yaw,UniversalDeltaTime,FreeLookCameraShiftDelta);
	FRotator CurrentRot = FRotator(FreeLookCharacterRot.Pitch,YawChange,FreeLookCharacterRot.Roll);
	MyPlayerControlRef->SetControlRotation(CurrentRot);*/
	
}

void ACoreCharacter::Sprint_Pressed()
{
	//TODO ADS CHECK
	if(bWalkingForwardBackward )
	{
		bIsSprinting = true ;
		/*if (bSlideButtonPressed)
		{
			bCanSlide=true;
		}
		if (bSlideButtonPressed==false)
		{
			bCanSlide=false;
		}*/
		
		if(bWalkingLeftRight && bWalkingForwardBackward)
		{
			bIsSprinting = true ;
			
		}
	}
	if(bWalkingLeftRight)
	{
		bIsSprinting=false;
		if(bWalkingForwardBackward)
		{
			bIsSprinting=false;
		}
	}
	if(bIsSprinting && bWalkingForwardBackward==false)
	{
		bIsSprinting=false;
	}

	if(bWalkingForwardBackward==false)
	{
		bIsSprinting=false;
	}
	
	
	/*
	if(GetCharacterMovement()->Velocity.Size()>0)
	{
		bIsSprinting=true;
		Playerstatus = EPlayerStatus::Sprinting_Gen ;
	}
	*/
	
}

void ACoreCharacter::Sprint_Released()
{
	
	bIsSprinting = false ;
	if(bWalkingForwardBackward == false)
	{
		bIsSprinting = false ;

		bCanSlide=false;
	}
	/*
	bIsSprinting=false;
	if(GetCharacterMovement()->Velocity.Size()>0)
	{
		if(bIsWalking)
		{
			Playerstatus = EPlayerStatus::Walking_Gen ;
		}
	}*/
}

void ACoreCharacter::Crouch_Pressed()
{
	bSlideButtonPressed = true;
	if(bIsSprinting)
	{
		bCanSlide=true;
	}
	else
	{
		bIsCrouching =true;
	}
	
	if(bIsCrouching)
	{
		ACharacter::Crouch();
	}
	if(bCanSlide)
	{
		Slide();
	}
}

void ACoreCharacter::Crouch_Released()
{
	bIsCrouching =false;
	bCanSlide=false;
	bSlideButtonPressed=false;
	ACharacter::UnCrouch();
}

void ACoreCharacter::Crouch_Axis(float Value)
{
	if (Value!=0)
	{
		if(bIsCrouching)
		{
			bIsCrouching = false;
			ACharacter::UnCrouch();
			return;
		}
		if(bIsCrouching==false)
		{
			if(bCanSlide==false)
			{
				bIsCrouching= true;
				ACharacter::Crouch();
				return;
			}
		
		}
	}

	
}

void ACoreCharacter::Slide()
{
	if(bCanSlide)
	{
		if(AM_Slide)
		{
			//PlayAnimMontage(AM_Slide,1);
		}
	
	}
}

void ACoreCharacter::Walk_Pressed()
{

	if(bIsSprinting)
	{
		return;
	}
	else
	bIsWalking = true ;
	/*if(bIsWalking)
	{
		
		bIsWalking=false;
		return;
	}
	if(bIsWalking==false)
	{
		bIsWalking = true ;
		return;
	}*/

	// you have to be in jog mode to enable that functiion
	/*
		if( bIsSprinting )
		{
			Playerstatus = EPlayerStatus::Sprinting_Gen ;
			
		}
		else
		{
			Playerstatus = EPlayerStatus::Walk
		}
	/*
		if(Playerstatus== EPlayerStatus::Walking_Gen)
		{
			bIsWalking=false;
			if(GetCharacterMovement()->Velocity.Size()>0)
			{
				if(bIsSprinting)
				{
					Playerstatus = EPlayerStatus::Sprinting_Gen ;
				}
				else
					Playerstatus = EPlayerStatus::Jog_Gen;
			}
			if(GetCharacterMovement()->Velocity.Size()==0)
			{
				Playerstatus=EPlayerStatus::Idle;
			}
	
			return;
			
		}*/
}

void ACoreCharacter::Walk_Released()
{
	bIsWalking = false ;
	
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
	PlayerInputComponent->BindAction("EquipWeapon_Primary",IE_Pressed,this,&ACoreCharacter::EquipeWeapon_Primary);
	PlayerInputComponent->BindAction("EquipWeapon_Secondary",IE_Pressed,this,&ACoreCharacter::EquipeWeapon_Secondary);
	PlayerInputComponent->BindAction("EquipWeapon_Melee",IE_Pressed,this,&ACoreCharacter::EquipeWeapon_Primary);
	PlayerInputComponent->BindAction("FreeLook",IE_Pressed,this,&ACoreCharacter::FreeLookup_Pressed);
	PlayerInputComponent->BindAction("FreeLook",IE_Released,this,&ACoreCharacter::FreeLookup_Released);
	PlayerInputComponent->BindAction("ADS", IE_Pressed, this, &ACoreCharacter::Ads_Pressed);
	PlayerInputComponent->BindAction("ADS", IE_Released, this, &ACoreCharacter::Ads_Released);
	PlayerInputComponent->BindAction("Fire",IE_Pressed,this,&ACoreCharacter::Fire);
	PlayerInputComponent->BindAction("Walk",IE_Pressed,this,&ACoreCharacter::Walk_Pressed);
	PlayerInputComponent->BindAction("Walk",IE_Released,this,&ACoreCharacter::Walk_Released);
	PlayerInputComponent->BindAction("Sprint",IE_Pressed,this,&ACoreCharacter::Sprint_Pressed);
	PlayerInputComponent->BindAction("Sprint",IE_Released,this,&ACoreCharacter::Sprint_Released);
	PlayerInputComponent->BindAction("Crouch",IE_Pressed,this,&ACoreCharacter::Crouch_Pressed);
	PlayerInputComponent->BindAction("Crouch",IE_Released,this,&ACoreCharacter::Crouch_Released);
	PlayerInputComponent->BindAxis("Crouch_AXIS", this,& ACoreCharacter::Crouch_Axis );
	
	
	

	

}

UAbilitySystemComponent* ACoreCharacter::GetAbilitySystemComponent() const
{

	return AbilitySystemComp ;
}

void ACoreCharacter::SetWeaponPosition()
{
	bWeaponShouldIdle = true ;
	GetWorldTimerManager().ClearTimer(WeaponPositionTimerHandle);

	
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

