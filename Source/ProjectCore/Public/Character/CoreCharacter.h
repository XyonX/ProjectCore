// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CharacterAttributeComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/CorePlayerController.h"
#include "AbilitySystemInterface.h"
#include "Abilities/GameplayAbility.h"
#include "Abilities/GameplayAbility.h"
#include "CoreCharacter.generated.h"

class UAbilitySystemComponent ;

class USpringArmComponent ;
class UCameraComponent ;
class APlayerController;
class UCharacterAttributeComponent;
UCLASS()
class PROJECTCORE_API ACoreCharacter : public ACharacter , public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACoreCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* CharacterMesh;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite , Category = "Camera")
	USpringArmComponent*SpringArm ;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Camera")
	UCameraComponent * Camera ;


private:
	


	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Character")
	float UniversalDeltaTime ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Character",meta = (ToolTip = "this is Idle to walk interp time chooose after trying  multiple value"))
	float IdleToWalkInterpTime ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Character" , meta = (ToolTip = "This is the walk Speed Multipliyer decide how fast character can Walkarround"))
	float WalkSpeedMultiplier ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Character")
	float TurnRate ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Character")
	float LookUpRate ;

	UFUNCTION()
	void MoveForward (float Value );
	UFUNCTION()
	void MoveRight (float Value) ;
	UFUNCTION()
	void Turn (float Value) ;
	UFUNCTION()
	void LookUp(float Value);
	//void Jump_Custom_Pressed ();
	

	UPROPERTY(VisibleAnywhere ,BlueprintReadWrite ,Category = "Character ")
	APlayerController*MyPlayerControlRef ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Character")
	APlayerController* PlayerController ;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	// Setting Up Getters
	FORCEINLINE  UCameraComponent* GetCameraComponent () {return Camera; }
	FORCEINLINE  APlayerController * GetPlayerController (){ return MyPlayerControlRef; }

	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Character")
	UCharacterAttributeComponent*AttributeComp;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Character")
	UAbilitySystemComponent*AbilitySystemComp;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const ;

	FORCEINLINE UCharacterAttributeComponent* GetCharacterAttributeComp () {return AttributeComp; }
	
	UFUNCTION(BlueprintCallable,Category="Character")
	void AquireAbility(TSubclassOf<UGameplayAbility>AbilityToAquire);
	
	

};
