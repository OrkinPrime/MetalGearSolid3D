// Fill out your copyright notice in the Description page of Project Settings.


#include "PPlayer.h"

APPlayer::APPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;
	
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));

	SpringArmComp->SetupAttachment(RootComponent);
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);

}

void APPlayer::BeginPlay()
{
	Super::BeginPlay();
}


void APPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!CameraInput.IsZero())
	{
		FRotator Rotation = SpringArmComp->GetComponentRotation();
		Rotation.Yaw += CameraInput.X;
		Rotation.Pitch += CameraInput.Y;
		SpringArmComp->SetWorldRotation(Rotation);
	}
}

void APPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("WS", this, &APPlayer::MoveForward);
	InputComponent->BindAxis("AD", this, &APPlayer::MoveRight);
	InputComponent->BindAxis("Mouse_X", this, &APPlayer::YawCamera);
	InputComponent->BindAxis("Mouse_Y", this, &APPlayer::PitchCamera);
	InputComponent->BindAction("Space", IE_Pressed, this, &APPlayer::StartJump);
	InputComponent->BindAction("Space", IE_Released, this, &APPlayer::StopJump);
	InputComponent->BindAction("Mouse_Left", IE_Pressed, this, &APPlayer::Fire);
	InputComponent->BindAction("LShift", IE_Pressed, this, &APPlayer::BeginSprint);
	InputComponent->BindAction("LShift", IE_Released, this, &APPlayer::EndSprint);
	InputComponent->BindAction("LCtrl", IE_Pressed, this, &APPlayer::BeginCrouch);
	InputComponent->BindAction("LCtrl", IE_Released, this, &APPlayer::EndCrouch);
}

void APPlayer::MoveForward(float AxisValue)
{
	if (AxisValue != 0) {
		if (AxisValue > 0) 
		{
			float Yaw = FRotator::NormalizeAxis(SpringArmComp->GetComponentRotation().Yaw - Controller->GetControlRotation().Yaw);
			Yaw = Controller->GetControlRotation().Yaw + Yaw;
			FRotator Rotation = Controller->GetControlRotation();
			Rotation.Yaw = FMath::Lerp(Controller->GetControlRotation().Yaw, Yaw, 0.3);
			Controller->SetControlRotation(Rotation);
		}
		else
		{
			float Yaw = FRotator::NormalizeAxis(SpringArmComp->GetComponentRotation().Yaw + 180 - Controller->GetControlRotation().Yaw);
			Yaw = Controller->GetControlRotation().Yaw + Yaw;
			FRotator Rotation = Controller->GetControlRotation();
			Rotation.Yaw = FMath::Lerp(Controller->GetControlRotation().Yaw, Yaw, 0.3);
			Controller->SetControlRotation(Rotation);
		}
		FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, FMath::Abs(AxisValue));
	}
}

void APPlayer::MoveRight(float AxisValue)
{
	if (AxisValue != 0) 
	{
		if (AxisValue > 0)
		{
			float Yaw = FRotator::NormalizeAxis(SpringArmComp->GetComponentRotation().Yaw + 90 - Controller->GetControlRotation().Yaw);
			Yaw = Controller->GetControlRotation().Yaw + Yaw;
			FRotator Rotation = Controller->GetControlRotation();
			Rotation.Yaw = FMath::Lerp(Controller->GetControlRotation().Yaw, Yaw, 0.3);
			Controller->SetControlRotation(Rotation);
		}
		else
		{
			float Yaw = FRotator::NormalizeAxis(SpringArmComp->GetComponentRotation().Yaw - 90 - Controller->GetControlRotation().Yaw);
			Yaw = Controller->GetControlRotation().Yaw + Yaw;
			FRotator Rotation = Controller->GetControlRotation();
			Rotation.Yaw = FMath::Lerp(Controller->GetControlRotation().Yaw, Yaw, 0.3);
			Controller->SetControlRotation(Rotation);
		}
		FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, FMath::Abs(AxisValue));
	}
}

void APPlayer::PitchCamera(float AxisValue)
{
	CameraInput.Y = AxisValue;
}

void APPlayer::YawCamera(float AxisValue)
{
	CameraInput.X = AxisValue;
}

void APPlayer::StartJump()
{
	bPressedJump = true;
}

void APPlayer::StopJump()
{
	bPressedJump = false;
}

void APPlayer::BeginSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void APPlayer::EndSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void APPlayer::BeginCrouch()
{
	Crouch();
}

void APPlayer::EndCrouch()
{
	UnCrouch();
}

void APPlayer::Fire()
{
	FVector Location;
	FVector Direction;
	Location = GetActorLocation();
	Direction = FRotationMatrix(SpringArmComp->GetComponentRotation()).GetScaledAxis(EAxis::X);
	Super::Fire(Location, Direction);
}