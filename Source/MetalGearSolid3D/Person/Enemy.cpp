// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "MetalGearSolid3D/Person/PPlayer.h"

AEnemy::AEnemy()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));

	BoxComponent->SetupAttachment(RootComponent);

	BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (PathFollowingComp)
	{
		switch (State)
		{
		case 0:
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(AIController, End);
			if (PathFollowingComp->GetStatus() == EPathFollowingStatus::Idle || PathFollowingComp->GetStatus() == EPathFollowingStatus::Waiting)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Success"));
				Swap(Start, End);
				State = 2;
			}
			break;
		case 1:
			if (Player != nullptr && FVector::Distance(GetActorLocation(), PlayerLocation) < WarningRange)
			{
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(AIController, PlayerLocation);
				//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Find Move"));
				if (PathFollowingComp->GetStatus() == EPathFollowingStatus::Idle || PathFollowingComp->GetStatus() == EPathFollowingStatus::Waiting)
				{
					FString str = "Find Move Success";
					str.Append(FString::FromInt((int)PlayerLocation.X)+" "+ FString::FromInt((int)PlayerLocation.Y) + " "+ FString::FromInt((int)PlayerLocation.Z));
					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red,str);
					if (FVector::Distance(GetActorLocation(), PlayerLocation) < WarningRange)
					{
						PlayerLocation = Player->GetActorLocation();
					}
					else
					{
						State = 2;
					}
				}
				if (FVector::Distance(GetActorLocation(), MoveLocation) < 0.1)
				{
					State = 2;
				}
				else
				{
					MoveLocation = GetActorLocation();
				}
			}
			else
			{
				State = 2;
			}
			break;
		case 2:
			WaitingTime += DeltaTime;
			if (WaitingTime >= 3)
			{
				WaitingTime = 0;
				State = 0;
			}
			break;
		default:
			break;
		}
		
	}
	if (IsDead())
	{
		Destroy();
	}
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	Start = GetActorLocation();
	End.Z = Start.Z;
	MoveLocation = Start;
	AIController = Cast<AAIController>(GetController());
	if (AIController)
	{
		PathFollowingComp = AIController->GetPathFollowingComponent();
	}
	FScriptDelegate Delegate;
	Delegate.BindUFunction(this, "OnOverlapBegin");
	BoxComponent->OnComponentBeginOverlap.AddUnique(Delegate);
}

void AEnemy::OnOverlapBegin(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Find"));
	auto temp = Cast<APPlayer>(OtherActor);
	if (temp != nullptr)
	{
		Player = temp;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Find Player"));
		State = 1;
		PlayerLocation = OtherActor->GetActorLocation();
	}
}
