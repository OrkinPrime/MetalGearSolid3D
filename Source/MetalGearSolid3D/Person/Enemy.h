// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Person.h"
#include "Enemy.generated.h"

/**
 * 
 */
UCLASS()
class METALGEARSOLID3D_API AEnemy : public APerson
{
	GENERATED_BODY()
public:
	AEnemy();
	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* HitComp,AActor* OtherActor,UPrimitiveComponent* OtherComp,int32 OtherBodyIndex,bool bFromSweep);
	UPROPERTY(EditAnywhere)
		AAIController* AIController;
	UPROPERTY(EditAnywhere)
		UBoxComponent* BoxComponent;
private:
	UPROPERTY(EditAnywhere)
		FVector Start;
	UPROPERTY(EditAnywhere)
		FVector End;
	UPROPERTY()
		FVector MoveLocation;
	UPROPERTY()
	UPathFollowingComponent* PathFollowingComp;
	UPROPERTY()
		int State = 0;
	UPROPERTY()
		class APPlayer* Player;
	UPROPERTY()
		FVector PlayerLocation;
	UPROPERTY(EditAnywhere)
		float WarningRange = 500;
	UPROPERTY()
		float WaitingTime = 0;
};
