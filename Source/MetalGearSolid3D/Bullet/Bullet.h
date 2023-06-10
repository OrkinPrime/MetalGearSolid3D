// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MetalGearSolid3D/Header.h"
#include "Bullet.generated.h"

UCLASS()
class METALGEARSOLID3D_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

	virtual void Tick(float DeltaTime) override;

	void SetDamage(float damage);
	int32 GetDamage();
	void SetSpeed(float speed);
	float GetSpeed();
	void SetVelocity(FVector Direction);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
		virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit);
	UPROPERTY(EditAnywhere)
		USphereComponent* SphereComponent;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* StaticMeshComponent;
	UPROPERTY(VisibleAnywhere, Category = Movement)
		UProjectileMovementComponent* ProjectileMovementComponent;

private:
	UPROPERTY(EditAnywhere, Category="Bullet")
		int32 Damage = 0;
	UPROPERTY(EditAnywhere, Category = "Bullet")
		float Speed = 0;
};
