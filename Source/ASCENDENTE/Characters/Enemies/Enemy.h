// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "..\Source\ASCENDENTE\Characters\BasicCharacter.h"
#include "Enemy.generated.h"

/**
 *
 */
UCLASS()
class ASCENDENTE_API AEnemy : public ABasicCharacter
{
	GENERATED_BODY()

public:
	AEnemy();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void LookAtPlayer();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayDeathAnimation();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayAttackAnimation();

public:
	void MarkForAbsolution();
	void ReactToHit();
	virtual void Attack();
	virtual void HandleDeath();

	UFUNCTION(BlueprintImplementableEvent)
	void DoKnockback();

	bool bIsMarkedForAbsolution = false;

	class ASen *GetSenReference() { return SenReference; }

private:
	UPROPERTY(EditAnywhere, Category = "Absolution")
	int AbsolutionTime = 30;

	void DisableAbsolution();
	void ReturnSpriteToNormal();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UPaperFlipbookComponent* EnemySpriteFlipbook;

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateBlackboardAggro();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateIsDead();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Aggro")
	float AggroRange = 800;

	UPROPERTY(BlueprintReadOnly, Category = "Aggro")
	bool doesPlayerHasAggro = false;

	UPROPERTY(BlueprintReadOnly, Category = "Lifetime")
	bool isDead = false;

	UPROPERTY(BlueprintReadOnly, Category = "Effects")
	float HitColorDuration = 0.4f;

	void CheckPlayerDistance();

	class ASen *SenReference;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent *ProjectileSpawnPoint;
};
