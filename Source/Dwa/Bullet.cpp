// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"


// Sets default values
ABullet::ABullet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet Mesh"));
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(5);
	//FRotator StartRotation = GetActorRotation();
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FRotator StartRotation = GetActorRotation();
	if (StartRotation.Yaw > -10 && StartRotation.Yaw < 10)
	{
		FVector NewLocation = GetActorLocation();
		NewLocation.Y -= Velocity;
		SetActorLocation(NewLocation);
	}
	if (StartRotation.Yaw > 80 && StartRotation.Yaw < 100)
	{
		FVector NewLocation = GetActorLocation();
		NewLocation.X += Velocity;
		SetActorLocation(NewLocation);
	}
	if (StartRotation.Yaw > 170 || StartRotation.Yaw < -170)
	{
		FVector NewLocation = GetActorLocation();
		NewLocation.Y += Velocity;
		SetActorLocation(NewLocation);
	}
	if (StartRotation.Yaw > -100 && StartRotation.Yaw < -80)
	{
		FVector NewLocation = GetActorLocation();
		NewLocation.X -= Velocity;
		SetActorLocation(NewLocation);
	}


}

