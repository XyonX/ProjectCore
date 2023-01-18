// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CharacterAttributeComponent.h"

// Sets default values for this component's properties
UCharacterAttributeComponent::UCharacterAttributeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
	DefaultHealth = 100 ;
}

void UCharacterAttributeComponent::BeginPlay()
{

	Super::BeginPlay();
	Health=DefaultHealth;
	AActor* MyOwner = GetOwner();
	if (MyOwner)
	{
		
		MyOwner->OnTakeAnyDamage.AddDynamic(this, &UCharacterAttributeComponent::HandleTakeAnyDamage);
	}
	
	
}


bool UCharacterAttributeComponent::ApplyHealthChange(float Delta)
{
	Health =FMath::Clamp(Health-Delta,0,DefaultHealth);
	if(OnHealthChangeAtrriBute.IsBound())
	{
		TestDeligate.Broadcast(69696969);
		OnHealthChangeAtrriBute.Broadcast(nullptr,this,Health,Delta);
	}
	return true ;
}

void UCharacterAttributeComponent::HandleTakeAnyDamage(AActor* DamagedActor, float Damage,
	const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{

	if (Damage <= 0.0f)
	{
		return;
	}
	Health = FMath::Clamp(Health - Damage, 0.0f, DefaultHealth);

	OnGettingDamage.Broadcast(this,Health,Damage,DamageType,InstigatedBy,DamageCauser);
	
}
