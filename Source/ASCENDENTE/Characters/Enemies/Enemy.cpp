// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "../Source/ASCENDENTE/Characters/Sen/Sen.h"
#include "PaperSpriteComponent.h"
#include "Components/CapsuleComponent.h"
#include "../Source\ASCENDENTE\Components\HealthComponent.h"
#include "Kismet/KismetMathLibrary.h"

AEnemy::AEnemy()
{
    EnemySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Enemy Sprite"));
    EnemySprite->SetupAttachment(RootComponent);

    ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile SpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(RootComponent);
}

void AEnemy::BeginPlay()
{
    Super::BeginPlay();

    auto PlayerRef = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    SenReference = Cast<ASen>(PlayerRef);

    UHealthComponent *HealthComponent = Cast<UHealthComponent>(GetComponentByClass(UHealthComponent::StaticClass()));
    UpdateHealth(HealthComponent->GetHealth());
}

void AEnemy::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    CheckPlayerDistance();
    UpdateBlackboardAggro();
    LookAtPlayer();
}

void AEnemy::MarkForAbsolution()
{
    DrawDebugSphere(GetWorld(), GetActorLocation(), 200, 12, FColor::Yellow, false, AbsolutionTime);
    bIsMarkedForAbsolution = true;

    FTimerHandle AbsolutionTimerHandler;
    GetWorldTimerManager().SetTimer(AbsolutionTimerHandler, this, &AEnemy::DisableAbsolution, AbsolutionTime, false);
}

void AEnemy::DisableAbsolution()
{
    bIsMarkedForAbsolution = false;
}

void AEnemy::CheckPlayerDistance()
{
    FVector SenLocation = SenReference->GetActorLocation();
    float Distance = FVector::Distance(SenLocation, GetActorLocation());
    doesPlayerHasAggro = (Distance < AggroRange);
}

void AEnemy::ReactToHit()
{
    EnemySprite->SetSpriteColor(FColor::FromHex("FF0000FF"));
    FTimerHandle ColorHandler;
    GetWorldTimerManager().SetTimer(ColorHandler, this, &AEnemy::ReturnSpriteToNormal, HitColorDuration, false);
}

void AEnemy::ReturnSpriteToNormal()
{
    EnemySprite->SetSpriteColor(FColor::FromHex("FFFFFFFF"));
}

void AEnemy::LookAtPlayer()
{
    FVector PlayerLocation = UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorLocation();
    FVector EnemyLocation = GetActorLocation();

    FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(EnemyLocation, PlayerLocation);

    SetActorRotation(FQuat::MakeFromRotator(LookAtRotation));
}

void AEnemy::Attack() {}