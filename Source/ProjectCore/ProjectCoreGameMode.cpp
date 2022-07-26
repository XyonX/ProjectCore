// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectCoreGameMode.h"
#include "ProjectCoreCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProjectCoreGameMode::AProjectCoreGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
