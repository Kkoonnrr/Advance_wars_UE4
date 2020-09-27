// Fill out your copyright notice in the Description page of Project Settings.


#include "Factoryy.h"
#include "Tank.h"
#include "Components/BoxComponent.h"
// Sets default values
AFactoryy::AFactoryy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	FactoryMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Factory Mesh"));
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;
	FactoryMesh->AttachTo(RootComponent);
}

// Called when the game starts or when spawned
void AFactoryy::BeginPlay()
{
	Super::BeginPlay();
	Create = false;
}

void AFactoryy::CreateTank()
{
	if (Create == true)
	{
		VCreateRot = GetActorRotation();
		VCreateLoc = GetActorLocation() + FVector(500.f, 0.f, 0.f);
		FActorSpawnParameters CreatePar;
		AActor* SpawnedActorRef = GetWorld()->SpawnActor<AActor>(ActorToSpawn, VCreateLoc, VCreateRot, CreatePar);
		Create = false;
	}

}

// Called every frame
void AFactoryy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

