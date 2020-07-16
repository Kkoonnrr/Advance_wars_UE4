// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "DwaCharacter.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "something.generated.h"

UCLASS()
class DWA_API Asomething : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Asomething();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float RunningTime;
	float Yaw;

	UPROPERTY(EditAnywhere)
		UShapeComponent* Box;

	UPROPERTY(EditDefaultsOnly)
		UStaticMeshComponent* SM_Block;

	UPROPERTY(EditAnywhere)
		float SpeedScale;

	FVector PlayerLocation = FVector(-1548.0f, 897.0f, 684.0f);
	/*UFUNCTION()
		void TriggerEnter(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	*/
	FVector BoxSize = FVector(2.0f, 2.0f, 2.0f);

	UPROPERTY(EditAnywhere)
		bool YAxis = true;

	UPROPERTY(EditAnywhere, category = "Rotating")
		float Rotate;

	ADwaCharacter* MyPlayerController;

	UPROPERTY(EditAnywhere)
		FString ItemName = FString(TEXT(""));

	void PickUp();

	void GetPlayer(AActor* Player);

	bool BItemIsInRange = false;

	UFUNCTION()
		void TriggerEnter(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void TriggerExit(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
