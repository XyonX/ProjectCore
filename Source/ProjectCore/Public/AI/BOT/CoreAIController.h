// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "CoreAIController.generated.h"

class UBehaviorTree;
/**
 * 
 */
UCLASS()
class PROJECTCORE_API ACoreAIController : public AAIController
{
	GENERATED_BODY()
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly ,Category="AI")
	UBehaviorTree* BehaviorTree;

	
};
