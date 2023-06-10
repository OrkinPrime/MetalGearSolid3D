// Fill out your copyright notice in the Description page of Project Settings.


#include "Person.h"
#include "MetalGearSolid3D/Bullet/Bullet.h"

// Sets default values
APerson::APerson()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BulletClass = LoadClass<ABullet>(nullptr, TEXT("/Script/Engine.Blueprint'/Game/BP/Bullet/BP_Bullet.BP_Bullet_C'"), nullptr, LOAD_None, nullptr);
}

// Called when the game starts or when spawned
void APerson::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APerson::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APerson::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APerson::Fire(FVector Location,FVector Direction)
{
	if (BulletClass != nullptr)
	{
		auto Bullet = GetWorld()->SpawnActor<ABullet>(BulletClass, Location,FRotator::ZeroRotator);
		Bullet->SetVelocity(Direction);
	}
}

void APerson::SetHp(int32 hp)
{
	this->Hp = hp;
}

int32 APerson::GetHp()
{
	return Hp;
}

bool APerson::IsDead()
{
	if (Hp <= 0)
	{
		return true;
	}
	return false;
}