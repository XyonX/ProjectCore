// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_Find_Target_In_Radius.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCORE_API UBTService_Find_Target_In_Radius : public UBTService
{
	GENERATED_BODY()

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;


	
	UPROPERTY(EditAnywhere,Category="AI")
	FBlackboardKeySelector  RandomLocation ;
	UPROPERTY(EditAnywhere,Category="AI")
	FBlackboardKeySelector  CheckLineTrace ;
	UPROPERTY(EditAnywhere,Category="AI")
	FBlackboardKeySelector  InAttackRange ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AI")
	float Radius = 3000 ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AI")
	float LineTraceRange = 1000 ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AI")
	float AttackRange = 500 ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AI")
	bool bShouldLineTrace ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AI")
	bool bInAttackRange ;
	
};
