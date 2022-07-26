// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/CoreAnimInstance.h"
#include"Character/CoreCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

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
	if(MyCharacterRef)
	{
		FVector Velocity = MyCharacterRef->GetVelocity();
		Velocity.Z=0.f;
		Speed=Velocity.Size();

		bIsInAir = MyCharacterRef->GetCharacterMovement()->IsFalling();
		bIsAccelerating= MyCharacterRef->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f ? true : false ;
	}
}
