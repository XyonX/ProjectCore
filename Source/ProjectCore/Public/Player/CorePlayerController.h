// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"
#include "Components/InputComponent.h"
#include "CorePlayerController.generated.h"


class USpringArmComponent;
class UCameraComponent;

UCLASS()
class PROJECTCORE_API ACorePlayerController : public APlayerController
{
	GENERATED_BODY()
	ACorePlayerController();
	
};
