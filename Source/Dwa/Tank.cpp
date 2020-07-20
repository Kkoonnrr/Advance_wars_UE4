// Fill out your copyright notice in the Description page of Project Settings.

#include "Math/Rotator.h"
#include "Bullet.h"
#include "Marker.h"
#include "Tank.h"
#include "Components/BoxComponent.h"
#include "Containers/UnrealString.h"
#include "Engine.h"
#include "Math/UnrealMathUtility.h"
// Sets default values
ATank::ATank()
{

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Tank = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tank Mesh"));
	RootComponent = Box;
	Tank->AttachTo(RootComponent);
	Health = 10.f;
	Choosen = false;
	Left = true;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!Left && rot != 179.f)
	{
		NewRotation = NewRotation + FRotator(0.f, 1.f, 0.f);
		if (NewRotation.Yaw > 181) NewRotation.Yaw = -179;
		SetActorRotation(NewRotation);
		rot = NewRotation.Yaw;
		GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString::Printf(TEXT("%f"), rot));
	}
	else
		Left = true;
}

void ATank::DamageTaken(float Damage)
{
	Health -= Damage;
	if (Health <= 0.f)
	{
		DestroyTank();

	}
}

void ATank::Choice(bool Choose)
{
	if (Choose)
	{
		FVector ActorLocation = GetActorLocation();
		FRotator ActorRotation = GetActorRotation();
		FVector MarkerLocation = ActorLocation + FVector(0, 0, 300);
		FRotator MarkerRotation = ActorRotation;
		FActorSpawnParameters MarkerParams;
		AActor* SpawnedActorRef = GetWorld()->SpawnActor<AActor>(MarkerToSpawn, MarkerLocation, MarkerRotation);
		FHitResult* HitResult = new FHitResult();
		FVector StartTrace = GetActorLocation() + FVector(0.f, 0.f, 0.f);
		FVector ForwardVector = FVector(0.f, 0.f, 1.f);
		FVector EndTrace = ((ForwardVector * 2000.f) + StartTrace);
		FCollisionQueryParams TraceParams;
		TraceParams.AddIgnoredActor(this);
		if (GetWorld()->LineTraceSingleByChannel(*HitResult, StartTrace, EndTrace, ECC_Visibility, TraceParams))
		{
			GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString::Printf(TEXT("cos")));
			TestTarget = Cast<AMarker>(HitResult->Actor.Get());
		}
	}
	else 
	{
		if (TestTarget != NULL)
		{
			GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString::Printf(TEXT("Itemmmmm")));
			TestTarget->MarkerDestroy();
		}
	}
}

void ATank::DestroyTank()
{
	Destroy();
}

void ATank::Hitt()
{
	UWorld* const World = GetWorld();
	FVector ActorLocation = GetActorLocation();
	FRotator ActorRotation = GetActorRotation();
	//Roll = GetActorLocation().Roll;
	//Pitch = GetActorLocation().Pitch;
	//Yaw = GetActorLocation().Yaw;
	FVector SpawnLocation = ActorLocation + FVector(0, 0, 67);
	FRotator SpawnRotation = ActorRotation;
	FActorSpawnParameters SpawnParams;
	AActor* SpawnedActorRef = GetWorld()->SpawnActor<AActor>(ActorToSpawn, SpawnLocation, SpawnRotation, SpawnParams);
}
void ATank::TMove(float Axis, bool sign)
{
	if (Axis == 1 && sign == false)
	{
		FVector ActorLocation = GetActorLocation();
		FVector NewLocation = ActorLocation + FVector(-forward, 0.f, 0.f);
		SetActorLocation(NewLocation);
		TestTarget->MMove(Axis, -forward);
	}
	else if (Axis == 1 && sign == true)
	{
		FVector ActorLocation = GetActorLocation();
		FVector NewLocation = ActorLocation + FVector(forward, 0.f, 0.f);
		SetActorLocation(NewLocation);
		TestTarget->MMove(Axis, forward);
	}
	else if (Axis == 2 && sign == false)
	{
		FVector ActorLocation = GetActorLocation();
		FVector NewLocation = ActorLocation + FVector(0.f, -forward, 0.f);
		SetActorLocation(NewLocation);
		TestTarget->MMove(Axis, -forward);
	}
	else if (Axis == 2 && sign == true)
	{
		FVector ActorLocation = GetActorLocation();
		FVector NewLocation = ActorLocation + FVector(0.f, forward, 0.f);
		NewRotation = GetActorRotation();
		rot = NewRotation.Yaw;
		if (rot != 179.f && rot < 170.f || rot != 179.f && rot > - 170.f)
			Left = false;
		//NewRotation = FRotator(0.f, 180.f, 0.f);
		//SetActorRotation(NewRotation);
		SetActorLocation(NewLocation);
		TestTarget->MMove(Axis, forward);
		//for (rot; 90 > rot; rot++)
			//Tick(1.f);
	}
}	
int ATank::Mod(float one, float two)
{
	int a = two / one;
	int b = a * one;
	int c = two - b;
	return c;
}

