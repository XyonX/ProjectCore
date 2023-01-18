// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Character/CoreCharacter_AI.h"

// Sets default values
ACoreCharacter_AI::ACoreCharacter_AI()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACoreCharacter_AI::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACoreCharacter_AI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

