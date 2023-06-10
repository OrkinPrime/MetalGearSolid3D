// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Person.h"
#include "PPlayer.generated.h"

/**
 * 
 */
UCLASS()
class METALGEARSOLID3D_API APPlayer : public APerson
{
	GENERATED_BODY()
	
public:
	APPlayer();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		void StartJump();
	UFUNCTION()
		void StopJump();

	void BeginSprint();//将角色移动速度设置为冲刺值。
	void EndSprint();//将角色移动速度设置回默认速度值。
	void BeginCrouch();//角色蹲伏请求
	void EndCrouch();//角色结束蹲伏请求
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void PitchCamera(float AxisValue);
	void YawCamera(float AxisValue);
	void Fire();
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		USpringArmComponent* SpringArmComp;
	UPROPERTY(EditAnywhere)
		UCameraComponent* CameraComp;
private:
	FVector2D CameraInput;
	UPROPERTY(EditAnywhere)
		float WalkSpeed = 400.F;
	UPROPERTY(EditAnywhere)
		float SprintSpeed = 600.F;
};
