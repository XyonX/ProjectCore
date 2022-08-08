// Fill out your copyright notice in the Description page of Project Settings.


#include "Utilities/CoreProjectile.h"

#include "Components/CharacterAttributeComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/CharacterAttributeComponent.h"
// Sets default values
ACoreProjectile::ACoreProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>("SphereComp");
	RootComponent=CollisionSphere;

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp ->SetupAttachment(RootComponent);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 1000.f;
	MovementComp->bRotationFollowsVelocity = true ;
	MovementComp ->bInitialVelocityInLocalSpace = true;

	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this,&ACoreProjectile::OnOverlapBegin);
	Damage = 20;
}

// Called when the game starts or when spawned
void ACoreProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACoreProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACoreProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if(OtherActor)
	{

		UCharacterAttributeComponent*CharacterAttribute = Cast<UCharacterAttributeComponent>(  OtherActor->GetComponentByClass(UCharacterAttributeComponent::StaticClass()));
		if(CharacterAttribute)
		{
			CharacterAttribute->ApplyHealthChange(-Damage);
			Destroy();
		}
	}
}

