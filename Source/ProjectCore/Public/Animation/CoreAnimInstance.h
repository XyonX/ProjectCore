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
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UPROPERTY(BlueprintReadOnly,Category="AnimInstance",meta = (AllowPrivateAccess="true"));
	class ACoreCharacter*MyCharacterRef;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="AnimInstance",meta = (AllowPrivateAccess="true"));
	float Speed ;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="AnimInstance",meta = (AllowPrivateAccess="true"));
	bool bIsInAir ;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="AnimInstance",meta = (AllowPrivateAccess="true"));
	bool bIsAccelerating ;


	// offset yaw for straffing 
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AnimInstance",meta = (AllowPrivateAccess="true"))
	float MovementOffset ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AnimInstance",meta = (AllowPrivateAccess="true"))
	float LastMovementOffset ;
	
	
	
	
};
