// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MyBTService_CheckAttackRange.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void UMyBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);


	//  Check Distance Between Bot Anf Player

	UBlackboardComponent* BlackBoardComp =   OwnerComp.GetBlackboardComponent();

	if( ensure(BlackBoardComp))
	{
		 AActor* TargetActor = Cast<AActor>(BlackBoardComp->GetValueAsObject("TargetActor"));

		if(TargetActor)
		{

			AAIController*MyController = OwnerComp.GetAIOwner(); 

			if(ensure(MyController))
			{
				APawn*AIPawn = MyController->GetPawn();
				if(ensure(AIPawn))
				{

					float DistanceTo =   FVector::Distance(TargetActor->GetActorLocation(),AIPawn->GetActorLocation());
					bool bWithinRange = DistanceTo <Range ;

					bool bHasLineOfSight = false ;
					
					if(bWithinRange)
					{
						bHasLineOfSight = MyController->LineOfSightTo(TargetActor);
					}
					

					BlackBoardComp->SetValueAsBool(AttackRangeKey.SelectedKeyName,bWithinRange && bHasLineOfSight );
				}
				
			}
			
		}
	}
	  
	
}
