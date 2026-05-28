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

	UFUNCTION(BlueprintImplementableEvent)
	void StartShootPrimary();

	UFUNCTION(BlueprintImplementableEvent)
	void OnEnemyConnect(FVector EnemyLocation);

	UPROPERTY(EditAnywhere, Category = "Ammo")
	float PrimaryAmmoCost;

	bool bReadyToFire = true;

protected:
	UFUNCTION(BlueprintCallable)
	virtual void ShootPrimary();

	UPROPERTY(EditAnywhere, Category = "Damage")
	float FireDamage;
	UPROPERTY(EditAnywhere, Category = "Cooldown")
	float FireRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UPaperFlipbookComponent *WeaponFlipbook;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent *ProjectileSpawnPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent *SceneRoot;
};
