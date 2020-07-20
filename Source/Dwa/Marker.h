// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Marker.generated.h"

UCLASS()
class DWA_API AMarker : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMarker();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	void MMove(float Axis, float value);
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void MarkerDestroy();
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Marker;
	UPROPERTY(EditAnywhere)
		UShapeComponent* Box;
};
