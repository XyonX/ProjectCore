// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CoreAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCORE_API UCoreAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UCoreAnimInstance();

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:

	// handle turn in place variable
	void TurnInPlace();
	void TurnInPlaceCustom();

private:
	UPROPERTY(BlueprintReadOnly,Category="AnimInstance",meta = (AllowPrivateAccess="true"));
	class ACoreCharacter*MyCharacterRef;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AnimInstance",meta = (AllowPrivateAccess="true"))
	APlayerController*ControllerRef;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="AnimInstance",meta = (AllowPrivateAccess="true"));
	float Speed ;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="AnimInstance",meta = (AllowPrivateAccess="true"));
	bool bIsInAir ;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="AnimInstance",meta = (AllowPrivateAccess="true"));
	bool bIsAccelerating ;
	bool bAiming;


	// offset yaw for straffing 
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AIM Offset",meta = (AllowPrivateAccess="true"))
	float MovementOffset ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AIM Offset",meta = (AllowPrivateAccess="true"))
	float LastMovementOffset ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AIM Offset",meta = (AllowPrivateAccess="true"))
	float AimOffset_Yaw;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AIM Offset",meta = (AllowPrivateAccess="true"))
	float AimOffset_Pitch;


	// yaw of the character this frame
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Turn In Place",meta = (AllowPrivateAccess="true"))
	float CharacterYaw;
	// yaw of the character previous frame
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Turn In Place",meta = (AllowPrivateAccess="true"))
	float CharacterYawLastFrame;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Turn In Place",meta = (AllowPrivateAccess="true"))
	float RootYawOffset;
	float RotationCurve;
	float RotationCurveLastFrame;

	// For Custom Turn In Place

	// the Control  Rotation Offset Respect TO the Character Position
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=" Custom Turn In Place",meta = (AllowPrivateAccess="true"))
	FRotator RotationOffset;

	// Yaw In The  Previous Frame 
	float YawLastFrame;
	// Yaw In The Curent Frame 
	float CurrentYaw;

	// YAW ofFSET Is Already Defined Previously
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=" Custom Turn In Place",meta = (AllowPrivateAccess="true"))
	float YawOffset;
	
	
	
	
};
