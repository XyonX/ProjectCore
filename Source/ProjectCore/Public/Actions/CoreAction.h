// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"
#include "CoreAction.generated.h"

class UWorld ;
class UCoreActionComponent ;

USTRUCT()
struct FActionRepData
{
	GENERATED_BODY()

public:

	UPROPERTY()
	bool bIsRunning;

	UPROPERTY()
	AActor* Instigator;
};


UCLASS(Blueprintable)
class PROJECTCORE_API UCoreAction : public UObject
{
	GENERATED_BODY()
protected:

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="UI")
	TSoftObjectPtr<UTexture2D> Icon ;

	UPROPERTY(Replicated)
	UCoreActionComponent* ActionComp;
	UFUNCTION(BlueprintCallable, Category = "Action")
	UCoreActionComponent*GetOwningComponent()const ;

	UPROPERTY(EditDefaultsOnly , Category = "Tags")
	FGameplayTagContainer GrantTags ;
	UPROPERTY(EditDefaultsOnly , Category = "Tags")
	FGameplayTagContainer BlockedTags ;

	UPROPERTY(ReplicatedUsing="OnRep_RepData")
	FActionRepData RepData ;

	UPROPERTY(Replicated)
	float TimeStarted ;

	UFUNCTION()
	void OnRep_RepData();

public:
	
	void Initialize(UCoreActionComponent*NewActionComp);


	UPROPERTY(EditDefaultsOnly,Category = "Actions")
	bool bAutoStart ;
	
	UFUNCTION(BlueprintCallable, Category = "Action")
	bool IsRunning() const;


	UFUNCTION(BlueprintNativeEvent,Category="Action")
	bool CanStart(AActor*Instigator);

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category ="Action")
	void StartAction(AActor*Instigator);

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category ="Action")
	void StopAction(AActor*Instigator);

	UPROPERTY(EditDefaultsOnly ,Category = "Action"  )
	FName ActionName ; 

	
	UWorld* GetWorld()const override ;
	
	/*bool IsSuportedForNetworking () const override
	{
		return true ;
	}*/
};
