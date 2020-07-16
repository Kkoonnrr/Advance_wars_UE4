// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tank.generated.h"

UCLASS()
class DWA_API ATank : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATank();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere)
		UShapeComponent* Box;

	UPROPERTY(EditDefaultsOnly)
		UStaticMeshComponent* Tank;

	FVector PlayerLocation = FVector(-1548.0f, 897.0f, 684.0f);
	float Health;
	float Roll;
	float Pitch;
	float Yaw;
	void DamageTaken(float Damage);

	void DestroyTank();

	void Hitt();

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
		TSubclassOf<class AActor> ActorToSpawn;
};
