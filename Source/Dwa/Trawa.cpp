// Fill out your copyright notice in the Description page of Project Settings.


#include "Trawa.h"

// Sets default values
ATrawa::ATrawa()
{
	SM_Block = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh"));
	//OnMove = CreateDefaultSubobject<UMaterial>(TEXT("OnMove"));
	//OffMove = CreateDefaultSubobject<UMaterial>(TEXT("OffMove"));
}

// Called when the game starts or when spawned
void ATrawa::BeginPlay()
{
	Super::BeginPlay();
	//SM_Block->SetMaterial(0, OffMove);
}

void ATrawa::ChangeMaterial()
{
	SM_Block->SetMaterial(0, OnMove);
}

