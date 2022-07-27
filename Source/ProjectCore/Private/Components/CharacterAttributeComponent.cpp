// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CharacterAttributeComponent.h"

// Sets default values for this component's properties
UCharacterAttributeComponent::UCharacterAttributeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
	Health = 100 ;
}


bool UCharacterAttributeComponent::ApplyHealthChange(float Delta)
{
	Health +=Delta;
	return true ;
}

