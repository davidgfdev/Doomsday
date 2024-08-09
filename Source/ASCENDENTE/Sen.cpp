// Fill out your copyright notice in the Description page of Project Settings.

#include "Sen.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"

ASen::ASen()
{
    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArmComponent->SetupAttachment(RootComponent);

    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    CameraComponent->SetupAttachment(SpringArmComponent);
}

// Called to bind functionality to input
void ASen::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("Aim"), this, &ASen::Aim);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ASen::Turn);
}

void ASen::BeginPlay()
{
    Super::BeginPlay();

    SenPlayerController = Cast<APlayerController>(GetController());
}

void ASen::Aim(float Value)
{
    if (SenPlayerController)
    {
        float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
        float AimValue = Value * SensibilityY * DeltaTime;
        SenPlayerController->AddPitchInput(AimValue);
    }
}

void ASen::Turn(float Value)
{
    if (SenPlayerController)
    {
        float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
        float TurnValue = Value * SensibilityX * DeltaTime;
        SenPlayerController->AddYawInput(TurnValue);
    }
}