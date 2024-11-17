// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponBase.h"
#include "PaperFlipbookComponent.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root"));
	RootComponent = SceneRoot;

	WeaponFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Weapon Flipbook"));
	WeaponFlipbook->SetupAttachment(SceneRoot);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile SpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(WeaponFlipbook);
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeaponBase::ShootPrimary()
{
}
void AWeaponBase::ShootSecondary()
{
}