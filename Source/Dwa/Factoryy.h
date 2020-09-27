// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Components/TextRenderComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Factoryy.generated.h"

UCLASS()
class DWA_API AFactoryy : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere)
		UShapeComponent* Box;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* FactoryMesh;
	// Sets default values for this actor's properties
	AFactoryy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
		TSubclassOf<class AActor> ActorToSpawn;
	FVector VCreateLoc;
	FRotator VCreateRot;
	bool Create;
	void CreateTank();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
