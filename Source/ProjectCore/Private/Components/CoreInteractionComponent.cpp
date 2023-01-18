// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CoreInteractionComponent.h"

#include "Camera/CameraComponent.h"
#include "Character/CoreCharacter.h"
#include "PickupObjects/Pickup_Base.h"
#include "Kismet/GameplayStatics.h"
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

	FVector2D ViewportSize2D;
	if(GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize(ViewportSize2D);
	}
	FVector2D CrossHairLoc(ViewportSize2D.X/2,ViewportSize2D.Y/2);

	bool bViewport3D;
	FVector ViewportLoc_3D;
	FVector ViewportDir_3D;
	FVector StartLoc_Viewport;
	FVector EndLocation_Viewport;
	
	// Projecting the 2d onto 3d
	 bViewport3D = UGameplayStatics::DeprojectScreenToWorld(UGameplayStatics::GetPlayerController(this,0),CrossHairLoc,ViewportLoc_3D,ViewportDir_3D);




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

	StartLoc_Viewport = ViewportLoc_3D;
	EndLocation_Viewport=StartLoc_Viewport+ViewportDir_3D*1000;
	if(GetWorld()->LineTraceSingleByObjectType(HitResult,StartLoc_Viewport,EndLocation_Viewport,QueryParam))
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

