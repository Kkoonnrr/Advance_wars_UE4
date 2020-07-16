// Fill out your copyright notice in the Description page of Project Settings.


#include "Trawa.h"

// Sets default values
ATrawa::ATrawa()
{
	SM_Block = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh"));
}

// Called when the game starts or when spawned
void ATrawa::BeginPlay()
{
	Super::BeginPlay();
	
}

