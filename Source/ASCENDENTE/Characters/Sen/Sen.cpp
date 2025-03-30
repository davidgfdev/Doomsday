// Fill out your copyright notice in the Description page of Project Settings.

#include "Sen.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"
#include "Shakes/LegacyCameraShake.h"
#include "..\Source\ASCENDENTE\Weapons\WeaponBase.h"
#include "..\Source\ASCENDENTE\Weapons\Nihilist.h"
#include "..\Source\ASCENDENTE\Weapons\HopeAndPrison.h"
#include "..\Source\ASCENDENTE\Characters\Enemies\Enemy.h"
#include "..\Source\ASCENDENTE\Components\HealthComponent.h"
#include "..\Source\ASCENDENTE\ASCENDENTEGameModeBase.h"

ASen::ASen()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetMobility(EComponentMobility::Movable);
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->SetMobility(EComponentMobility::Movable);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	WeaponArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("WeaponArm"));
	WeaponArmComponent->SetupAttachment(CameraComponent);

	Weapon = CreateDefaultSubobject<UChildActorComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(WeaponArmComponent);
}

// Called to bind functionality to input
void ASen::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
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

	CurrentAmmo = MaxAmmo;
	UpdateAmmo(CurrentAmmo);

	CurrentSpeed = StandardSpeed;
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

	if (HeadBobCameraShake)
	{
		HeadBob();
	}

	GetCharacterMovement()->MaxWalkSpeed = CurrentSpeed;
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
	UpdateCrosshairSize(Value);
}

void ASen::Strafe(float Value)
{
	StrafeAxisValue = Value;
	FVector RightDirection = UKismetMathLibrary::GetRightVector(GetActorRotation());
	AddMovementInput(RightDirection, Value);
	UpdateCrosshairSize(Value);
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
			AWeaponBase* CurrentWeapon = Cast<AWeaponBase>(Weapon->GetChildActor());
			if (!CurrentWeapon->IsA(AHopeAndPrison::StaticClass()) && CurrentAmmo >= CurrentWeapon->PrimaryAmmoCost && CurrentWeapon->bReadyToFire)
			{
				CurrentSpeed = NihilistSpeed;
				CurrentWeapon->StartShootPrimary();
				CurrentAmmo -= CurrentWeapon->PrimaryAmmoCost;
				UpdateAmmo(CurrentAmmo);
			}
		}
	}
	else
	{
		CurrentSpeed = StandardSpeed;
	}
}

void ASen::HPPrimaryFire()
{
	if (Weapon)
	{
		AWeaponBase* CurrentWeapon = Cast<AWeaponBase>(Weapon->GetChildActor());
		if (CurrentWeapon->IsA(AHopeAndPrison::StaticClass()) && CurrentWeapon->bReadyToFire)
		{
			CurrentWeapon->StartShootPrimary();
		}
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
			Weapon->GetChildActor()->SetOwner(this);
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

void ASen::HandleDeath()
{
	Respawn();
}

void ASen::Respawn() 
{
	UE_LOG(LogTemp, Display, TEXT("Respawning..."));

	if (UGameplayStatics::GetGameMode(GetWorld())->IsA(AASCENDENTEGameModeBase::StaticClass()))
	{
		UE_LOG(LogTemp, Display, TEXT("GameMode is ok..."));
		
		AASCENDENTEGameModeBase* GameMode = Cast<AASCENDENTEGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
		UE_LOG(LogTemp, Display, TEXT("RespawnLocation is %s"), *GameMode->RespawnLocation.ToString());
		if (!GameMode->RespawnLocation.IsZero())
		{
			MakeDeathEffect();
			UE_LOG(LogTemp, Display, TEXT("Setting actor location..."));
			SetActorLocation(GameMode->RespawnLocation);
			UHealthComponent* HealthComponent = Cast<UHealthComponent>(GetComponentByClass(UHealthComponent::StaticClass()));
			HealthComponent->Heal(100);
			UpdateHealth(HealthComponent->GetHealth());
		}
	}
}

void ASen::HeadBob()
{
	double VelocityLength = GetVelocity().Length();
	FVector NormalizedVelocity = GetVelocity();
	NormalizedVelocity.Normalize(0.0001f);
	double NormalizedVelocityLength = NormalizedVelocity.Length();

	if (VelocityLength > 0 && CanJump())
	{
		SenPlayerController->ClientStartCameraShake(HeadBobCameraShake, NormalizedVelocityLength * HeadbobFactor);
	}
}