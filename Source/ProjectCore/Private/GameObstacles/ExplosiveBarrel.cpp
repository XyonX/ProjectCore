// Fill out your copyright notice in the Description page of Project Settings.


#include "GameObstacles/ExplosiveBarrel.h"
#include"Particles/ParticleSystemComponent.h"

AExplosiveBarrel::AExplosiveBarrel()
{

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp ->SetupAttachment(RootComponent);
	Damage = 20 ;
}

void AExplosiveBarrel::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if(OtherActor)
	{
		ACoreCharacter * OverlappedCharacter = Cast<ACoreCharacter>(OtherActor);
		if(OverlappedCharacter)
		{
			OverlappedCharacter->GetCharacterAttributeComp()->ApplyHealthChange(Damage);
			
		}
	}
}
