// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/CoreActionComponent.h"
#include "Actions/CoreAction.h"
#include "Net/UnrealNetwork.h"
#include "ProjectCore/ProjectCore.h"
#include "Engine/ActorChannel.h"

DECLARE_CYCLE_STAT(TEXT("StartActionByName"), STAT_StartActionByName, STATGROUP_STANFORD);


// Sets default values for this component's properties
UCoreActionComponent::UCoreActionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	SetIsReplicatedByDefault(true);
}

void UCoreActionComponent::AddAction(AActor* Instigator, TSubclassOf<UCoreAction> ActionClass)
{
	if(!ensure(ActionClass))
	{
		return ;
	}
	if(!GetOwner()->HasAuthority())
	{
		UE_LOG(LogTemp,Warning , TEXT ("Client Attempting t AddAction [ class : %s ] ") , *GetNameSafe(ActionClass));
		return ;
	}

	UCoreAction*NewAction  = NewObject <UCoreAction>(GetOwner(),ActionClass);
	if(ensure (NewAction))
	{
		NewAction->Initialize(this);

		Actions.Add(NewAction);

		if (NewAction->bAutoStart && ensure(NewAction->CanStart(Instigator)))
		{
			NewAction->StartAction(Instigator);
		}
	}
	
}

void UCoreActionComponent::RemoveAction(UCoreAction* ActionToRemove)
{

	if (!ensure(ActionToRemove && !ActionToRemove->IsRunning()))
	{
		return;
	}

	Actions.Remove(ActionToRemove);
}

UCoreAction* UCoreActionComponent::GetAction(TSubclassOf<UCoreAction> ActionClass) const
{
	for (UCoreAction* Action : Actions)
	{
		if (Action && Action->IsA(ActionClass))
		{
			return Action;
		}
	}

	return nullptr;
}

bool UCoreActionComponent::StartActionByName(AActor* Instigator, FName ActionName)
{
	SCOPE_CYCLE_COUNTER(STAT_StartActionByName);

	for (UCoreAction* Action : Actions)
	{
		if (Action && Action->ActionName == ActionName)
		{
			if (!Action->CanStart(Instigator))
			{
				FString FailedMsg = FString::Printf(TEXT("Failed to run: %s"), *ActionName.ToString());
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FailedMsg);
				continue;
			}

			// Is Client?
			if (!GetOwner()->HasAuthority())
			{
				ServerStartAction(Instigator, ActionName);
			}

			// Bookmark for Unreal Insights
			TRACE_BOOKMARK(TEXT("StartAction::%s"), *GetNameSafe(Action));

			Action->StartAction(Instigator);
			return true;
		}
	}

	return false;
}

bool UCoreActionComponent::StopActionByName(AActor* Instigator, FName ActionName)
{
	for (UCoreAction* Action : Actions)
	{
		if (Action && Action->ActionName == ActionName)
		{
			if (Action->IsRunning())
			{
				// Is Client?
				if (!GetOwner()->HasAuthority())
				{
					ServerStopAction(Instigator, ActionName);
				}

				Action->StopAction(Instigator);
				return true;
			}
		}
	}

	return false ;
}


// Called when the game starts
void UCoreActionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	// Server Only
	if (GetOwner()->HasAuthority())
	{
		for (TSubclassOf<UCoreAction> ActionClass : DefaultActions)
		{
			AddAction(GetOwner(), ActionClass);
		}
	}
	
}

void UCoreActionComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// Stop all
	TArray<UCoreAction*> ActionsCopy = Actions;
	for (UCoreAction* Action : ActionsCopy)
	{
		if (Action && Action->IsRunning())
		{
			Action->StopAction(GetOwner());
		}
	}
}

void UCoreActionComponent::ServerStopAction_Implementation(AActor* Instigator, FName ActionName)
{
	StartActionByName(Instigator, ActionName);
}

void UCoreActionComponent::ServerStartAction_Implementation(AActor* Instigator, FName ActionName)
{
	StopActionByName(Instigator, ActionName);
}


// Called every frame
void UCoreActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

/*
bool UCoreActionComponent::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	return Super::ReplicateSubobjects(Channel, Bunch, RepFlags);
}


bool UCoreActionComponent::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UCoreActionComponent, Actions);

	
}*/

