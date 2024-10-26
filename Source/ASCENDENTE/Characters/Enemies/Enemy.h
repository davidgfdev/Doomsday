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

public:
	void MarkForAbsolution();
	void ReactToHit();
	virtual void Attack();

	bool bIsMarkedForAbsolution = false;

	class ASen *GetSenReference() { return SenReference; }

private:
	UPROPERTY(EditAnywhere, Category = "Absolution")
	int AbsolutionTime = 30;

	void DisableAbsolution();
	void ReturnSpriteToNormal();
	void LookAtPlayer();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UPaperSpriteComponent *EnemySprite;

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateBlackboardAggro();

	UPROPERTY(EditAnywhere, Category = "Aggro")
	float AggroRange = 800;

	UPROPERTY(BlueprintReadOnly, Category = "Aggro")
	bool doesPlayerHasAggro = false;

	UPROPERTY(BlueprintReadOnly, Category = "Effects")
	float HitColorDuration = 0.4f;

	void CheckPlayerDistance();

	class ASen *SenReference;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent *ProjectileSpawnPoint;
};
