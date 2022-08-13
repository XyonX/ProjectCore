// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CoreInteractionComponent.h"

#include "Camera/CameraComponent.h"
#include "Character/CoreCharacter.h"
#include "PickupObjects/Pickup_Base.h"
#include "Utilities/CoreInterface.h"

// Sets default values for this component's properties
UCoreInteractionComponent::UCoreInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCoreInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor*OwnerActor  = GetOwner();
	OwnerCharacter = Cast<ACoreCharacter>(OwnerActor);
}


// Called every frame
void UCoreInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCoreInteractionComponent::Interact_Comp() 
{


	FVector ViewpointLoc ;
	FRotator ViewpointRot ;
	OwnerCharacter->GetActorEyesViewPoint(ViewpointLoc,ViewpointRot);
	FHitResult HitResult;
	FVector StartLoc ;
	FRotator ControllerRotation ;
	FVector CameraLoc ; 
	FVector EndLoc ;
	if(OwnerCharacter)
	{
		CameraLoc = OwnerCharacter->GetCameraComponent()->GetComponentLocation();
		ControllerRotation = OwnerCharacter ->GetPlayerController()->GetControlRotation();
		EndLoc = ViewpointLoc + ControllerRotation.Vector()*1000;
	}
	FCollisionObjectQueryParams QueryParam ;
	QueryParam.AddObjectTypesToQuery(ECC_WorldDynamic);
	if(GetWorld()->LineTraceSingleByObjectType(HitResult,ViewpointLoc,EndLoc,QueryParam))
	{

		DrawDebugLine(GetWorld(),StartLoc,EndLoc,FColor::Green,false,5.0f );
		AActor*HitActor  = HitResult.GetActor() ;
		APickup_Base*PickupObject = Cast<APickup_Base>(HitActor);
		if(PickupObject)
		{
			
				if(PickupObject->GetClass()->ImplementsInterface(UCoreInterface::StaticClass()))
				{
					ICoreInterface::Execute_Interact(HitActor,OwnerCharacter);
					//Cast<ICoreInterface>(PickupObject->Interact_Implementation(OwnerCharacter));
					
				}
			
		}
		
	}
	
}

