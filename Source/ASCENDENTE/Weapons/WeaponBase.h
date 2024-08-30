// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

UCLASS()
class ASCENDENTE_API AWeaponBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeaponBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ShootPrimary(float &Ammo);
	virtual void ShootSecondary(float &Ammo);
	virtual void ShootMidAir(float &Ammo);

protected:
	UPROPERTY(EditAnywhere, Category = "Damage")
	float FireDamage;
	UPROPERTY(EditAnywhere, Category = "Cooldown")
	float FireRate;

	UPROPERTY(EditAnywhere, Category = "Ammo")
	float PrimaryAmmoCost;
	UPROPERTY(EditAnywhere, Category = "Ammo")
	float SecondaryAmmoCost;
	UPROPERTY(EditAnywhere, Category = "Ammo")
	float MidAirAmmoCost;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent *WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent *ProjectileSpawnPoint;
};
