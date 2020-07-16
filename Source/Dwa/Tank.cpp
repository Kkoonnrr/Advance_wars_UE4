// Fill out your copyright notice in the Description page of Project Settings.

#include "Math/Rotator.h"
#include "Bullet.h"
#include "Tank.h"
#include "Components/BoxComponent.h"
#include "Containers/UnrealString.h"
#include "Engine.h"
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

}

void ATank::DamageTaken(float Damage)
{
	Health -= Damage;
	if (Health <= 0.f)
	{
		DestroyTank();
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
	FVector SpawnLocation = ActorLocation + FVector(0, 0, 62);
	FRotator SpawnRotation = ActorRotation;
	FActorSpawnParameters SpawnParams;
	AActor* SpawnedActorRef = GetWorld()->SpawnActor<AActor>(ActorToSpawn, SpawnLocation, SpawnRotation, SpawnParams);
}

