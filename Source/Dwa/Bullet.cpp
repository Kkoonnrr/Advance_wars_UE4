// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Tank.h"
#include "DrawDebugHelpers.h"
#include "Math/Vector.h"
#include "Components/SceneComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"


// Sets default values
ABullet::ABullet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet Mesh"));
	int32 DamageAmount = 25;
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	begin = GetActorLocation();
	GetWorld()->GetTimerManager().SetTimer(Time, this, &ABullet::Damage, 0.2, false);
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

void ABullet::Damage()
{
	end = GetActorLocation();
	all = FVector(0.f, 0.f, 0.f);
	all = end - begin;
	FHitResult* HitResult = new FHitResult();
	FVector StartTrace = GetActorLocation() + FVector(0.f, 0.f, 0.f);
	FVector ForwardVector = all;
	FVector EndTrace = ((ForwardVector * 1.f) + StartTrace);
	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(this);
	//DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Green, false, 5.f);
	if (GetWorld()->LineTraceSingleByChannel(*HitResult, StartTrace, EndTrace, ECC_Visibility, TraceParams))
	{
		//GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString::Printf(TEXT("Yes")));
		TestTarget = Cast<ATank>(HitResult->Actor.Get());
		if (TestTarget != NULL)
		{
			TestTarget->DamageTaken(10.f);
			Destroy();
		}
		else Destroy();
	}
	else Destroy();
	//else if (GetWorld()->LineTraceSingleByChannel(*HitResult, StartTrace, EndTrace, ECC_Visibility, TraceParams) == NULL)
	
}

