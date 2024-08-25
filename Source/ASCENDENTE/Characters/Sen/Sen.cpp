// Fill out your copyright notice in the Description page of Project Settings.

#include "Sen.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"
#include "..\Source\ASCENDENTE\Weapons\WeaponBase.h"
#include "..\Source\ASCENDENTE\Weapons\Nihilist.h"
#include "..\Source\ASCENDENTE\Weapons\HopeAndPrison.h"

ASen::ASen()
{
    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArmComponent->SetupAttachment(RootComponent);

    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    CameraComponent->SetupAttachment(SpringArmComponent);

    Weapon = CreateDefaultSubobject<UChildActorComponent>(TEXT("Weapon"));
    Weapon->SetupAttachment(CameraComponent);
}

// Called to bind functionality to input
void ASen::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("Aim"), this, &ASen::Aim);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ASen::Turn);
    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ASen::MoveForward);
    PlayerInputComponent->BindAxis(TEXT("Strafe"), this, &ASen::Strafe);
    PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ASen::StartJump);
    PlayerInputComponent->BindAction(TEXT("Jump"), IE_Released, this, &ASen::StopJump);
    PlayerInputComponent->BindAction(TEXT("Dash"), IE_Pressed, this, &ASen::Dash);
    PlayerInputComponent->BindAxis(TEXT("PrimaryFire"), this, &ASen::PrimaryFire);
    PlayerInputComponent->BindAction(TEXT("HPPrimaryFire"), IE_Pressed, this, &ASen::HPPrimaryFire);
    PlayerInputComponent->BindAxis(TEXT("SecondaryFire"), this, &ASen::SecondaryFire);
    PlayerInputComponent->BindAction(TEXT("ChangeWeapon"), IE_Pressed, this, &ASen::ChangeWeapon);
}

void ASen::BeginPlay()
{
    Super::BeginPlay();

    SenPlayerController = Cast<APlayerController>(GetController());

    if (Weapons.Num() > 0)
    {
        Weapon->SetChildActorClass(Weapons[0]);
    }

    OriginalMaxSpeed = GetCharacterMovement()->GetMaxSpeed();
}

void ASen::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    BufferTime -= DeltaTime;

    if (GetMovementComponent()->IsFalling())
    {
        CoyoteTime -= DeltaTime;
        DashForce = DashForceAir;
    }
    else
    {
        CoyoteTime = CoyoteSeconds;
        DashForce = DashForceGround;
    }

    if (BufferTime >= 0 && CoyoteTime > 0 && !bCanDoubleJump)
    {
        Jump();
        bCanDoubleJump = true;
    }
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

void ASen::MoveForward(float Value)
{
    MoveForwardAxisValue = Value;
    FVector ForwardDirection = UKismetMathLibrary::GetForwardVector(GetActorRotation());
    AddMovementInput(ForwardDirection, Value);
}

void ASen::Strafe(float Value)
{
    StrafeAxisValue = Value;
    FVector RightDirection = UKismetMathLibrary::GetRightVector(GetActorRotation());
    AddMovementInput(RightDirection, Value);
}

void ASen::StartJump()
{
    BufferTime = BufferSeconds;

    if (bCanDoubleJump && GetCharacterMovement()->IsFalling())
    {
        Jump();
        bCanDoubleJump = false;
    }

    if (!GetCharacterMovement()->IsFalling())
    {
        bCanDoubleJump = false;
    }
}

void ASen::StopJump()
{
    StopJumping();
}

void ASen::Dash()
{
    if (bCanDash)
    {
        FVector ForwardDirection = UKismetMathLibrary::GetForwardVector(GetActorRotation()) * MoveForwardAxisValue;
        FVector RightDirection = UKismetMathLibrary::GetRightVector(GetActorRotation()) * StrafeAxisValue;

        FVector DashVector = ForwardDirection + RightDirection;
        LaunchCharacter(DashVector * DashForce, false, false);

        bCanDash = false;

        FTimerHandle DashCooldownTimerHandler;
        GetWorldTimerManager().SetTimer(DashCooldownTimerHandler, this, &ASen::DashCooldown, DashCooldownSeconds, false);
    }
}

void ASen::DashCooldown()
{
    bCanDash = true;
}

void ASen::PrimaryFire(float Value)
{
    if (Value == 1)
    {
        if (Weapon)
        {
            if (!Weapon->GetChildActor()->IsA(AHopeAndPrison::StaticClass()))
            {
                Cast<AWeaponBase>(Weapon->GetChildActor())->ShootPrimary();
            }
        }
    }
}

void ASen::HPPrimaryFire()
{
    if (Weapon)
    {
        if (Weapon->GetChildActor()->IsA(AHopeAndPrison::StaticClass()))
        {
            Cast<AWeaponBase>(Weapon->GetChildActor())->ShootPrimary();
        }
    }
}

void ASen::SecondaryFire(float Value)
{
    if (Value == 1)
    {
        if (GetCharacterMovement()->IsFalling())
        {
            MidAirFire();
        }
        else
        {
            if (Weapon)
            {
                if (!Weapon->GetChildActor()->IsA(AHopeAndPrison::StaticClass()))
                {
                    Cast<AWeaponBase>(Weapon->GetChildActor())->ShootSecondary();
                }
            }
        }
    }
    else if (Value == 0 && Weapon->GetChildActor()->IsA(ANihilist::StaticClass())) // SOLO PARA NIHILIST
    {
        Cast<ANihilist>(Weapon->GetChildActor())->RecoverMovement();
    }
}

void ASen::MidAirFire()
{
    if (Weapon)
    {
        Cast<AWeaponBase>(Weapon->GetChildActor())->ShootMidAir();
    }
}

void ASen::ChangeWeapon()
{
    if (Weapon)
    {
        if (Weapons.Num() > 0)
        {
            if (Weapon->GetChildActorClass() == Weapons[0])
            {
                Weapon->SetChildActorClass(Weapons[1]);
            }
            else
            {
                Weapon->SetChildActorClass(Weapons[0]);
            }
        }
    }
}

void ASen::SwitchMovementMode(bool bIsMoving)
{
    if (bIsMoving)
    {
        GetCharacterMovement()->MaxWalkSpeed = OriginalMaxSpeed;
    }
    else
    {
        GetCharacterMovement()->MaxWalkSpeed = 0.0f;
    }
}