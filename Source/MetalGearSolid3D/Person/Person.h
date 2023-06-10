// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MetalGearSolid3D/Header.h"
#include "Person.generated.h"

UCLASS()
class METALGEARSOLID3D_API APerson : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APerson();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		void Fire(FVector Location, FVector Direction);

	void SetHp(int32 hp);
	int32 GetHp();
	bool IsDead();
private:
	UPROPERTY(EditAnywhere, Category = "Person")
		int32 Hp = 1;
	UPROPERTY()
		UClass* BulletClass;
};
