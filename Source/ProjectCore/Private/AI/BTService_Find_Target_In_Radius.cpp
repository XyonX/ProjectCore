// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_Find_Target_In_Radius.h"

#include "AbstractNavData.h"
#include "AIController.h"
#include "CollisionDebugDrawingPublic.h"
#include "AI/NavigationSystemBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include"NavigationSystem.h"
#include "Kismet/GameplayStatics.h"
#include"AI/Navigation/NavigationTypes.h"

void UBTService_Find_Target_In_Radius::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
                                                float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent * BlackBoardComp =  OwnerComp.GetBlackboardComponent();
	if(ensure(BlackBoardComp))
	{

		AActor * TargetActor = Cast<AActor>( BlackBoardComp->GetValueAsObject("TargetActor"));

		if(TargetActor)
		{


			AAIController*MyController = OwnerComp.GetAIOwner();
			if(ensure(MyController))
			{
				APawn*MyPawn = MyController->GetPawn();

				if(ensure(MyPawn))
				{
					//UNavigationQueryFilter NavQuerry ;
					//NavQuerry.
				/*	FVector RandomLoc =  UNavigationSystemV1::GetRandomReachablePointInRadius(GetWorld()  , MyPawn->GetActorLocation(),Radius);
					float DistanceBetweenTargetAndRandomLocation =   FVector::Distance(RandomLoc,TargetActor->GetActorLocation());
					UE_LOG(LogTemp,Warning,TEXT("Distance Between the Random point And Target Actor is %f"),DistanceBetweenTargetAndRandomLocation)
					bShouldLineTrace = DistanceBetweenTargetAndRandomLocation <LineTraceRange ;
					float LineTraceRadius;
					if(bShouldLineTrace)
					{
						
						LineTraceRadius = DistanceBetweenTargetAndRandomLocation ;
						RandomLoc =  UNavigationSystemV1::GetRandomReachablePointInRadius(GetWorld() , TargetActor->GetActorLocation(),LineTraceRadius);
						
						//DrawLineTraces(MyPawn->GetActorEyesViewPoint() ,)
						//FNavLocation RandomNavLocation ;
						// bool  bNavLocationFound = AAbstractNavData::GetRandomReachablePointInRadius(TargetActor->GetActorLocation(),DistanceBetweenTargetAndRandomLocation , RandomNavLocation,nullptr,nullptr);
						
					}
					DistanceBetweenTargetAndRandomLocation =   FVector::Distance(TargetActor->GetActorLocation(),RandomLoc);
					//bInAttackRange = DistanceBetweenTargetAndRandomLocation<AttackRange;
					bInAttackRange = DistanceBetweenTargetAndRandomLocation<AttackRange;
					
					BlackBoardComp->SetValueAsBool(CheckLineTrace.SelectedKeyName,bShouldLineTrace);
					BlackBoardComp->SetValueAsBool(CheckLineTrace.SelectedKeyName,bInAttackRange);
					BlackBoardComp->SetValueAsVector(RandomLocation.SelectedKeyName,RandomLoc);*/
					
				}
				
			}
		}

		
	}
}
