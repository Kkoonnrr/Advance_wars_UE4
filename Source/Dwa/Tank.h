// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Components/TextRenderComponent.h"
#include "Marker.h"
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
private:
	//UPROPERTY(EditAnywhere, Category = BulletDecals);
	//UMaterialInterface* BulletHoleDecals;
	float Health;
	UTextRenderComponent* HealthText;
	void Text();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	int rot;
	AMarker* TestTarget;
	UPROPERTY(EditAnywhere)
		UShapeComponent* Box;
	void FindingBlocks(FVector Vector, int SrD);
	FVector Help1;
	FVector Help2;
	UPROPERTY(EditDefaultsOnly)
		UStaticMeshComponent* Tank;
	FRotator NewRotation;
	FVector PlayerLocation = FVector(-1548.0f, 897.0f, 684.0f);
	bool Move;
	bool Left;
	bool Right;
	bool Forward;
	bool Backward;
	bool Choosen;
	void DamageTaken(float Damage);
	void Choice(bool Choosen);
	void DestroyTank();
	void TMove(float Axis, bool sign);
	void TTMoveF(float Axis, bool sign);
	void TTMoveL(float Axis, bool sign);
	void TTMoveR(float Axis, bool sign);
	void TTMoveB(float Axis, bool sign);
	void Hitt();
	float TAxis;
	bool Tsign;
	bool Empty;
	int field;
	int MoveFLimit;
	float MoveTLimit;
	int Counter;
	int SpareMove;
	int SCounter;
	int Tap[10];
	FVector SpareStart;
	FVector SpareEnd;
	FVector Actor;
	FVector New;
	FVector VLeft;
	FVector VRight;
	FVector VForward;
	FVector VBackward;
	//ATrawa
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
		TSubclassOf<class AActor> ActorToSpawn;
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
		TSubclassOf<class AActor> MarkerToSpawn;
	UPROPERTY(EditDefaultsOnly, Category = "Moving")
		float forward;
	UPROPERTY(EditDefaultsOnly, Category = "MovementPoints")
		float MoveLimit;
	//UPROPERTY(EditDefaultsOnly, Category = "Moving")
		//float right;
	int Mod(float one, float two);
	UFUNCTION()
		void TriggerEnter(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult);
	//UFUNCTION()
		//void TriggerExit(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	void searching(float MoveL);
	void Deleting(float MoveL);
	void MinusMove(FVector Vector);

};
