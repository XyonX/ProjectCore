// Fill out your copyright notice in the Description page of Project Settings.


#include "GameObstacles/ExplosiveBarrel.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/GameplayStatics.h"
#include"Particles/ParticleSystemComponent.h"

AExplosiveBarrel::AExplosiveBarrel()
{

	
	Damage = 20 ;
}

void AExplosiveBarrel::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if(OtherActor)
	{
		UCharacterAttributeComponent*AttributeComp=  Cast<UCharacterAttributeComponent>(OtherActor->GetComponentByClass(UCharacterAttributeComponent::StaticClass()));
		if(AttributeComp)
		{
			AttributeComp->ApplyHealthChange(50);
		}
		/*ACoreCharacter * OverlappedCharacter = Cast<ACoreCharacter>(OtherActor);
		if(OverlappedCharacter)
		{
			OverlappedCharacter->GetCharacterAttributeComp()->ApplyHealthChange(Damage);
			if(ExplosionEffect)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),ExplosionEffect,GetActorLocation());
			}
			
			Destroy();
		}*/
	}
}
