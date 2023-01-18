// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterAttributeComponent.generated.h"

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChangedAttribute ,AActor*,InstigatorActor,UCharacterAttributeComponent* ,OwningComp ,  float , NewHealth,float ,Delta );

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FOnGettingDamageSignature,UCharacterAttributeComponent *,AttributeComponent,float,Health,float,Damage,const class UDamageType* ,DamageType,class AController* ,InstigatedBy,AActor*,DamageCauser);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTestDelegate, float, Damage);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTCORE_API UCharacterAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterAttributeComponent();
	virtual void BeginPlay() override;

	

protected:

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="CharacterAttribute")
	float DefaultHealth;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="CharacterAttribute")
	float Health;

	//TODO Setup Max Health

public:

	UFUNCTION(BlueprintCallable,Category="CharacterAttribute")
	bool ApplyHealthChange(float Delta);
	
	void HandleTakeAnyDamage(AActor* DamagedActor,float Damage,const class UDamageType* DamageType,class AController* InstigatedBy,AActor*DamageCauser);

	UPROPERTY(BlueprintAssignable,Category="Events")
	FOnGettingDamageSignature OnGettingDamage ;

	UPROPERTY(BlueprintAssignable,Category="Events")
	FOnHealthChangedAttribute OnHealthChangeAtrriBute ;

	UPROPERTY(BlueprintAssignable)
	FTestDelegate TestDeligate ;

	
		
};
