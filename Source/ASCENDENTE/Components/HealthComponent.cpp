// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthComponent.h"
#include "..\Source\ASCENDENTE\ASCENDENTEGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "../Source\ASCENDENTE\Characters\BasicCharacter.h"
#include "../Source\ASCENDENTE\Characters\Enemies\Enemy.h"
#include "../Source\ASCENDENTE\Characters\Sen\Sen.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor *Owner = GetOwner();

	if (Owner)
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
	}

	Health = MaxHealth;

	ASCENDENTEGameModeBase = Cast<AASCENDENTEGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (Owner->IsA(ASen::StaticClass()))
	{
		Cast<ASen>(Owner)->UpdateHealth(Health);
	}
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHealthComponent::DamageTaken(AActor *DamagedActor, float Damage, const UDamageType *DamageType, class AController *Instigator, AActor *DamageCauser)
{
	if (Damage <= 0.f)
		return;

	Health -= Damage;
	if (GetOwner()->IsA(ASen::StaticClass())) 
	{
		Cast<ASen>(GetOwner())->UpdateHealth(Health);
		Cast<ASen>(GetOwner())->MakeDamageEffect();
	}
		

	if (GetOwner()->IsA(AEnemy::StaticClass())){
		Cast<AEnemy>(GetOwner())->ReactToHit();
	}

	if (Health <= 0.f && ASCENDENTEGameModeBase)
	{
		ASCENDENTEGameModeBase->ActorDied(DamagedActor);
	}
}

void UHealthComponent::Heal(float Ammount)
{
	Health += Ammount;
	if (Health > MaxHealth)
	{
		Health = MaxHealth;
	}
}
