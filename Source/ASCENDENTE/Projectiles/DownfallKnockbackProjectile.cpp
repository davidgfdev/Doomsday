#include "DownfallKnockbackProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetMathLibrary.h>
#include "..\Source\ASCENDENTE\Characters\Sen\Sen.h"


void ADownfallKnockbackProjectile::ApplyHitEffects(FHitResult Hit) 
{
	ProjectileMovement->StopMovementImmediately();
	ProjectileMesh->SetSimulatePhysics(false);

	FTimerHandle StickBeforeExplodeHandle;
	GetWorldTimerManager().SetTimer(StickBeforeExplodeHandle, this, &ADownfallKnockbackProjectile::Explode, SecondsToExplode, false);
}

void ADownfallKnockbackProjectile::Explode() 
{
	TArray<AActor*> EnemiesInRange;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_PhysicsBody));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
	TArray<AActor*> ActorsToIgnore;
	AActor* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	ActorsToIgnore.Add(PlayerPawn);

	UKismetSystemLibrary::SphereOverlapActors(GetWorld(),
		GetActorLocation(),
		ExpansiveRadius,
		ObjectTypes,
		ACharacter::StaticClass(),
		ActorsToIgnore,
		EnemiesInRange);

	for (int i = 0; i < EnemiesInRange.Num(); i++)
	{
		ACharacter* Enemy = Cast<ACharacter>(EnemiesInRange[i]);
		FVector ProjectedLocation = GetActorLocation();
		ProjectedLocation.Z = Enemy->GetActorLocation().Z;
		FVector DirectionFromPlayer = Enemy->GetActorLocation() - ProjectedLocation;
		Enemy->LaunchCharacter(DirectionFromPlayer * ExpansiveImpulse, false, false);
		auto MyOwnerInstigator = GetOwner()->GetInstigatorController();
		auto DamageType = UDamageType::StaticClass();
		UGameplayStatics::ApplyDamage(Enemy, Damage, MyOwnerInstigator, GetOwner(), DamageType);
		UE_LOG(LogTemp, Display, TEXT("Enemy detected"));
	}

	Destroy();
}