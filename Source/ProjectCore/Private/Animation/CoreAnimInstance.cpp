// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/CoreAnimInstance.h"

#include "SAdvancedRotationInputBox.h"
#include"Character/CoreCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include"Kismet/GameplayStatics.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Kismet/KismetMathLibrary.h"

UCoreAnimInstance::UCoreAnimInstance() :
Speed(0.0f),
bIsInAir(false),
bIsAccelerating(false),
MovementOffset(0.0f),
LastMovementOffset(0.0f),
CharacterYaw(0.0f),
CharacterYawLastFrame(0.0f),
RootYawOffset(0.0f)
{

}

void UCoreAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	MyCharacterRef = Cast<ACoreCharacter>(TryGetPawnOwner());
}

void UCoreAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if(MyCharacterRef == nullptr)
	{
		MyCharacterRef = Cast<ACoreCharacter>(TryGetPawnOwner());
	}

	ControllerRef = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if(MyCharacterRef)
	{
		FVector Velocity = MyCharacterRef->GetVelocity();
		Velocity.Z=0.f;
		Speed=Velocity.Size();

		bIsInAir = MyCharacterRef->GetCharacterMovement()->IsFalling();
		bIsAccelerating= MyCharacterRef->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f ? true : false ;

		FRotator AimRotation = MyCharacterRef->GetBaseAimRotation();
		FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(MyCharacterRef->GetVelocity());

		MovementOffset = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation,AimRotation).Yaw;

		if(ControllerRef)
		{
		       /*
			if(ControllerRef->GetControlRotation().Yaw<180.0f)
			{
				AimOffset_Yaw = (ControllerRef->GetControlRotation().Yaw-MyCharacterRef->GetActorRotation().Yaw);
			}
			if(ControllerRef->GetControlRotation().Yaw>180.0f && MyCharacterRef->GetActorRotation().Yaw<= 0.0f)
			{
				float ControlYaw =  (360.0f- ControllerRef->GetControlRotation().Yaw);
				AimOffset_Yaw = - (ControlYaw+MyCharacterRef->GetActorRotation().Yaw);
			}
			if(ControllerRef->GetControlRotation().Pitch<180.0)
			{
				AimOffset_Pitch = ControllerRef->GetControlRotation().Pitch-MyCharacterRef->GetActorRotation().Pitch;
			}
			if(ControllerRef->GetControlRotation().Pitch>180.0f && MyCharacterRef->GetActorRotation().Pitch<= 0.0f)
			{
				float ControlPitch =  (360.0f- ControllerRef->GetControlRotation().Pitch);
				AimOffset_Pitch= - ( ControlPitch+MyCharacterRef->GetActorRotation().Pitch);
			}*/
			
		
		}
		
		//AimOffset_Pitch = MyCharacterRef->MyPlayerControlRef->GetControlRotation().Pitch-MyCharacterRef->GetActorRotation().Pitch;
		if(bIsAccelerating)
		{
			LastMovementOffset=MovementOffset;
			
		}
		bAiming=MyCharacterRef->bInADSMode;
	}
	//TurnInPlace();
	TurnInPlaceCustom();
}

void UCoreAnimInstance::TurnInPlace()

{

	if(MyCharacterRef==nullptr)return;
	if(Speed>0)
	{
		RootYawOffset=0.0f;
		CharacterYaw=MyCharacterRef->GetActorRotation().Yaw;
		CharacterYawLastFrame=0;
		RotationCurveLastFrame=0;
		RotationCurve=0.0f;
		
		
	}
	else
	{
		//  Value From Last Frame Every Frame We Are Storing The Character Rotationyaw
		CharacterYawLastFrame=CharacterYaw;
		// then we are Getting The Actor Rotation Yaw 
		CharacterYaw=MyCharacterRef->GetActorRotation().Yaw;
		// Every Frame We Are Subtracting The RootYaw With the Last Framw  YAw
		const float YawDelta {CharacterYaw-CharacterYawLastFrame};

		//Adding The Root Yaw Offset EveryFrame
		RootYawOffset =UKismetMathLibrary::NormalizeAxis(RootYawOffset-YawDelta);

		const float Turning (GetCurveValue(TEXT("Turning")));
		if(Turning>0)
		{
			RotationCurveLastFrame=RotationCurve;
			RotationCurve=GetCurveValue(TEXT("Rotation"));
			const float YawDelta_Anim{RotationCurve-RotationCurveLastFrame};
			RootYawOffset>0? RootYawOffset -=YawDelta_Anim : 	RootYawOffset+=YawDelta_Anim;

			const float ABSRootYawOffset {FMath::Abs(RootYawOffset)};
			if(ABSRootYawOffset>90.0f)
			{
				const float YawExcess {ABSRootYawOffset-90.0f};
				RootYawOffset>0 ? RootYawOffset -=YawExcess : RootYawOffset +=YawExcess;
			}
		}
	}
}

void UCoreAnimInstance::TurnInPlaceCustom()
{
	if(Speed>0)
	{

		YawOffset=0.0f;
		CurrentYaw = RotationOffset.Yaw	;
		YawLastFrame=CurrentYaw;
				
	}
	else
	{
		if(ControllerRef)
		{
			FRotator  CharactrRotation = MyCharacterRef->GetActorRotation();
			FRotator ControlRotation = ControllerRef->GetControlRotation();

			RotationOffset =  UKismetMathLibrary::NormalizedDeltaRotator(ControlRotation,CharactrRotation);

		
			YawLastFrame = CurrentYaw ;
			CurrentYaw = RotationOffset.Yaw	;

			float DeltaYaw = CurrentYaw-YawLastFrame;

			YawOffset = FMath::Clamp(YawOffset+DeltaYaw , -90,90);
			MyCharacterRef->YawOffset_Player=YawOffset;
		}
	}
	
}
