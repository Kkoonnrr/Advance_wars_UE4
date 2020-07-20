// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Marker.h"
#include "Components/BoxComponent.h"
// Sets default values
AMarker::AMarker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Marker = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Marker Mesh"));
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
}

// Called when the game starts or when spawned
void AMarker::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMarker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMarker::MarkerDestroy()
{
	Destroy();
}
void AMarker::MMove(float Axis, float value)
{
	if (Axis == 1)
	{
		FVector ActorLocation = GetActorLocation();
		FVector NewLocation = ActorLocation + FVector(value, 0.f, 0.f);
		SetActorLocation(NewLocation);
	}
	else
	{
		FVector ActorLocation = GetActorLocation();
		FVector NewLocation = ActorLocation + FVector(0.f, value, 0.f);
		SetActorLocation(NewLocation);
	}
}

