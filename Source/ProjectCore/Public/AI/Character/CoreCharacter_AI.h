// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CoreCharacter_AI.generated.h"

UCLASS()
class PROJECTCORE_API ACoreCharacter_AI : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACoreCharacter_AI();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
