// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tank.h"
#include "Bullet.generated.h"

UCLASS()
class DWA_API ABullet : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	FTimerHandle Time;
	FVector all;
	FVector begin;
	FVector end;
	float i;
	ATank* TestTarget;
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* BulletMesh;
	UFUNCTION()
		void Damage();
	UPROPERTY(EditAnywhere, Category = "Speed")
		float Velocity;
private:
	UPROPERTY(EditAnywhere, Category = BulletDecal)
	UMaterialInterface* BulletHolrDecal;
};
