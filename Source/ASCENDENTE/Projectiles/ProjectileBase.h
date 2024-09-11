// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

UCLASS()
class ASCENDENTE_API AProjectileBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectileBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void ApplyHitEffects(FHitResult Hit);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent *ProjectileMesh;

	UPROPERTY(EditAnywhere)
	float Damage = 50.f;

private:
	UPROPERTY(VisibleAnywhere, Category = "Movement")
	class UProjectileMovementComponent *ProjectileMovement;

	UPROPERTY(EditAnywhere)
	bool bItDestroysOnTouch = true;

	UFUNCTION()
	void OnHit(UPrimitiveComponent *HitComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit);
};
