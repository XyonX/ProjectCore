// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FOnHealthChangedSignature,UHealthComponent*,HelthComp,float,Health,float,HealthDelta,const class UDamageType* ,DamageType,class AController* ,InstigatedBy,AActor*,DamageCauser);

UCLASS( ClassGroup=(INFINITY), meta=(BlueprintSpawnableComponent) )
class PROJECTCORE_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Character Attributes")
	float Default_Health;
	UPROPERTY(BlueprintReadOnly,Category="CharacterAttribute")
	float Health;

	void HandleTakeAnyDamage(AActor* DamagedActor,float Damage,const class UDamageType* DamageType,class AController* InstigatedBy,AActor*DamageCauser);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable,Category="Events")
	FOnHealthChangedSignature OnHealthChanged ;
	
		
};
