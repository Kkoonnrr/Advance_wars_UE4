// Fill out your copyright notice in the Description page of Project Settings.

#include "something.h"
#include "Components/BoxComponent.h"
#include "Containers/UnrealString.h"
#include "Engine.h"
// Sets default values
Asomething::Asomething()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetGenerateOverlapEvents(true);
	//Box->OnComponentBeginOverlap.AddDynamic(this, &Asomething::TriggerEnter);
	Box->OnComponentBeginOverlap.AddDynamic(this, &Asomething::TriggerEnter);
	Box->OnComponentEndOverlap.AddDynamic(this, &Asomething::TriggerExit);
	Box->SetRelativeScale3D(BoxSize);
	RootComponent = Box;
	SM_Block = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box Mesh"));

	SpeedScale = 0.0f;
	SM_Block->AttachTo(RootComponent);
	Rotate = 0.f;
}
void Asomething::GetPlayer(AActor* Player)
{
	MyPlayerController = Cast<ADwaCharacter>(Player);
}
void Asomething::PickUp()
{
	MyPlayerController->Inventory.Add(*ItemName);
	GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Green, FString::Printf(TEXT("you pick the item up")));
	Destroy();
}
// Called when the game starts or when spawned
void Asomething::BeginPlay()
{
	Super::BeginPlay();
	Yaw = GetActorRotation().Yaw;
}

// Called every frame
void Asomething::Tick(float DeltaTime)
{
	if (MyPlayerController != NULL)
	{
		if (MyPlayerController->BIsPickingUp && BItemIsInRange)
		{
			PickUp();
		}
	}
	FRotator NewRotation = GetActorRotation();
	//float Yaw = NewRotation.Yaw;
	Super::Tick(DeltaTime);
	FVector NewLocation = GetActorLocation();
	float DeltaHeight = (FMath::Cos(RunningTime + DeltaTime));
	FQuat QuatRotation = FQuat(FRotator(0, 180, 0));
	UE_LOG(LogTemp, Warning, TEXT("%f"), Yaw);
	if (FMath::Cos(RunningTime)*FMath::Cos(RunningTime + DeltaTime)<=0)
	{
		AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);
		/*if (NewRotation.Yaw < 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Tak"));
			while (Yaw + 180 > NewRotation.Yaw)
			{
				UE_LOG(LogTemp, Warning, TEXT("tak"));
				//FQuat QuatRotation = FQuat(FRotator(0, Rotate, 0));
				AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);
				NewRotation = GetActorRotation();
			}
		}
		else if (NewRotation.Yaw >= 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Nie"));
			while (Yaw - 180 < NewRotation.Yaw)
			{
				UE_LOG(LogTemp, Warning, TEXT("nie"));
				//FQuat QuatRotation = FQuat(FRotator(0, Rotate, 0));
				AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);
				NewRotation = GetActorRotation();
			}
		}
		Yaw = NewRotation.Yaw;*/
	}
	//FQuat QuatRotation = FQuat(FRotator(0, Rotate, 0));
	//AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);	
	if (YAxis)
	NewLocation.Y += DeltaHeight * SpeedScale;
	else 
	NewLocation.X += DeltaHeight * SpeedScale;
	RunningTime += DeltaTime;
	SetActorLocation(NewLocation);
}

/*void Asomething::TriggerEnter(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OtherActor->SetActorLocation(PlayerLocation);
}*/

void Asomething::TriggerEnter(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult)
{
	BItemIsInRange = true;
	GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Green, FString::Printf(TEXT("Press e to pick up %s"), *ItemName));
	GetPlayer(OtherActor);
}
void Asomething::TriggerExit(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	BItemIsInRange = false;
}