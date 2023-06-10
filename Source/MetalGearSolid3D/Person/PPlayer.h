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

	void BeginSprint();//����ɫ�ƶ��ٶ�����Ϊ���ֵ��
	void EndSprint();//����ɫ�ƶ��ٶ����û�Ĭ���ٶ�ֵ��
	void BeginCrouch();//��ɫ�׷�����
	void EndCrouch();//��ɫ�����׷�����
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
