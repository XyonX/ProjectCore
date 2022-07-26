// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CoreCharacter.h"
#include "UObject/Interface.h"
#include "CoreInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCoreInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTCORE_API ICoreInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent , Category ="Interface Function")
	void Interact (ACoreCharacter*InstigatorCharacter);

	UFUNCTION()
	virtual void InteractPure(ACoreCharacter*InstigatorCharacter) = 0;
	
};
