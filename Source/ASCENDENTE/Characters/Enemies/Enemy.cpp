// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "../Source/ASCENDENTE/Characters/Sen/Sen.h"
#include "PaperSpriteComponent.h"
#include "Components/CapsuleComponent.h"
#include "../Source\ASCENDENTE\Components\HealthComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "PaperFlipbookComponent.h"

AEnemy::AEnemy()
{
    EnemySpriteFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Enemy Sprite"));
    EnemySpriteFlipbook->SetupAttachment(RootComponent);

    ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile SpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(RootComponent);
}

void AEnemy::BeginPlay()
{
    Super::BeginPlay();

    auto PlayerRef = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    SenReference = Cast<ASen>(PlayerRef);

    UHealthComponent *HealthComponent = Cast<UHealthComponent>(GetComponentByClass(UHealthComponent::StaticClass()));
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
    if (SenReference)
    {
        FVector SenLocation = SenReference->GetActorLocation();
        float Distance = FVector::Distance(SenLocation, GetActorLocation());
        doesPlayerHasAggro = (Distance < AggroRange);
    }
}

void AEnemy::ReactToHit()
{
    EnemySpriteFlipbook->SetSpriteColor(FColor::FromHex("FF0000FF"));
    FTimerHandle ColorHandler;
    GetWorldTimerManager().SetTimer(ColorHandler, this, &AEnemy::ReturnSpriteToNormal, HitColorDuration, false);
}

void AEnemy::ReturnSpriteToNormal()
{
    EnemySpriteFlipbook->SetSpriteColor(FColor::FromHex("FFFFFFFF"));
}

void AEnemy::LookAtPlayer()
{
    if (SenReference)
    {
        FVector PlayerLocation = SenReference->GetActorLocation();
        FVector EnemyLocation = GetActorLocation();

        FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(EnemyLocation, PlayerLocation);

        SetActorRotation(FQuat::MakeFromRotator(LookAtRotation));
    }
}

void AEnemy::Attack() 
{
    PlayAttackAnimation();
}

void AEnemy::HandleDeath()
{
    PlayDeathAnimation();
    isDead = true;
    UpdateIsDead();
}