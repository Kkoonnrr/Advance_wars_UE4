// Fill out your copyright notice in the Description page of Project Settings.

#include "DwaCharacter.h"
#include "Math/Rotator.h"
#include "Bullet.h"
#include "Marker.h"
#include "Tank.h"
#include "Trawa.h"
#include "Components/BoxComponent.h"
#include "Containers/UnrealString.h"
#include "Engine.h"
#include "Math/UnrealMathUtility.h"
// Sets default values
ATank::ATank()
{
	Health = 100.f;
	HealthText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("HealthText"));
	HealthText->SetWorldSize(100.f);
	HealthText->SetTextRenderColor(FColor::Blue);
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetGenerateOverlapEvents(true);
	RootComponent = Box;
	Tank = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tank Mesh"));
	Tank->AttachTo(RootComponent);
	HealthText->AttachTo(RootComponent);
	Choosen = false;
	Left = true;
	Right = true;
	Forward = true;
	Backward = true;
	Move = false;
	Empty = false;
	TAxis = 0;
	Tsign = false;
	VLeft = FVector(0.f, 500.f, 0.f);
	VRight = FVector(0.f, -500.f, 0.f);
	VForward = FVector(500.f, 0.f, 0.f);
	VBackward = FVector(-500.f, 0.f, 0.f);
	Actor = GetActorLocation();
	New = GetActorLocation();
	Box->OnComponentBeginOverlap.AddDynamic(this, &ATank::TriggerEnter);
	//Box->OnComponentEndOverlap.AddDynamic(this, &ATank::TriggerExit);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	//FVector dupa = (0.f, 0.f, 0.f);
	Super::BeginPlay();
	Actor = GetActorLocation();
	New = GetActorLocation();
	HealthText->SetText(FString::Printf(TEXT("Health: %0.1lf"), Health));
	//HealthText->SetRelativeLocation(dupa);
	Text();
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!Left && rot != 179.f && !Left && rot != 180.f && !Left && rot != 181.f)
	{
		NewRotation = NewRotation + FRotator(0.f, 0.2f, 0.f);
		if (NewRotation.Yaw > 181) NewRotation.Yaw = -179;
		SetActorRotation(NewRotation);
		rot = NewRotation.Yaw;
		//GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString::Printf(TEXT("%f"), rot));
	}
	else if (!Left && New.Y != Actor.Y + forward && Empty == true && -0.5 < MoveLimit)
	{
		New.Y++;// -= FVector(1.f, 0.f, 0.f);
		SetActorLocation(New);
		//GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString::Printf(TEXT("%f"), New.Y));
	}
	else if (!Left)
	{
		Empty = false;
		Left = true;
		TTMoveL(TAxis, Tsign);
	}
	if (!Forward && rot != -90.f && rot != -91.f && rot != -89.f)
	{
		NewRotation = NewRotation + FRotator(0.f, 0.2f, 0.f);
		if (NewRotation.Yaw > 181) NewRotation.Yaw = -179;
		SetActorRotation(NewRotation);
		rot = NewRotation.Yaw;
		//GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString::Printf(TEXT("1")));
		//GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString::Printf(TEXT("%f"), New.X));
	}
	else if (!Forward && New.X != Actor.X-forward && Empty == true && -0.5 < MoveLimit)
	{
		New.X--;// -= FVector(1.f, 0.f, 0.f);
		SetActorLocation(New);
		//GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString::Printf(TEXT("%f"), New.X));
	}
	else if (!Forward)
	{
		//GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString::Printf(TEXT("3")));
		Empty = false;
		Forward = true;
		TTMoveF(TAxis, Tsign);
	}
	if (!Right && rot != 0.f && rot != -1.f && rot != -1.f)
	{
		NewRotation = NewRotation + FRotator(0.f, 0.2f, 0.f);
		if (NewRotation.Yaw > 181) NewRotation.Yaw = -179;
		SetActorRotation(NewRotation);
		rot = NewRotation.Yaw;
		//GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString::Printf(TEXT("%f"), rot));
	}
	else if (!Right && New.Y != Actor.Y - forward && Empty == true && -0.5 < MoveLimit)
	{
		New.Y--;// -= FVector(1.f, 0.f, 0.f);
		SetActorLocation(New);
		//GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString::Printf(TEXT("%f"), New.Y));
	}
	else if (!Right)
	{
		Empty = false;
		Right = true;
		TTMoveR(TAxis, Tsign);
	}
	if (!Backward && rot != 90.f && rot != 91.f && rot != 89.f)
	{
		NewRotation = NewRotation + FRotator(0.f, 0.2f, 0.f);
		if (NewRotation.Yaw > 181) NewRotation.Yaw = -179;
		SetActorRotation(NewRotation);
		rot = NewRotation.Yaw;
		//GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString::Printf(TEXT("%f"), rot));
	}
	else if (!Backward && New.X != Actor.X + forward && Empty == true && -0.5 < MoveLimit)
	{
		New.X++;// -= FVector(1.f, 0.f, 0.f);
		SetActorLocation(New);
		//GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString::Printf(TEXT("%f"), New.X));
	}
	else if (!Backward)
	{

		Empty = false;
		Backward = true;
		TTMoveB(TAxis, Tsign);
	}
}

void ATank::DamageTaken(float Damage)
{
	Health -= Damage;
	HealthText->SetText(FString::Printf(TEXT("Health: %0.1lf"), Health));
	if (Health <= 0.f)
	{
		DestroyTank();
	}
}

void ATank::Choice(bool Choose)
{
	if (Choose)
	{
		FVector ActorLocation = GetActorLocation();
		FRotator ActorRotation = GetActorRotation();
		FVector MarkerLocation = ActorLocation + FVector(0, 0, 300);
		FRotator MarkerRotation = ActorRotation;
		FActorSpawnParameters MarkerParams;
		AActor* SpawnedActorRef = GetWorld()->SpawnActor<AActor>(MarkerToSpawn, MarkerLocation, MarkerRotation);
		FHitResult* HitResult = new FHitResult();
		FVector StartTrace = GetActorLocation() + FVector(0.f, 0.f, 0.f);
		FVector ForwardVector = FVector(0.f, 0.f, 1.f);
		FVector EndTrace = ((ForwardVector * 2000.f) + StartTrace);
		FCollisionQueryParams TraceParams;
		TraceParams.AddIgnoredActor(this);
		if (GetWorld()->LineTraceSingleByChannel(*HitResult, StartTrace, EndTrace, ECC_Visibility, TraceParams))
		{
			//GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString::Printf(TEXT("cos")));
			TestTarget = Cast<AMarker>(HitResult->Actor.Get());
		}

		/*TArray<FHitResult> HitResults;
		HitResults.Init(FHitResult(ForceInit), 10);
		MoveFLimit = 0;
		Counter = 0;
		do
		{
			FVector StartTr = GetActorLocation() - FVector(0.f, 0.f, 500.f)+ FVector(0.f+(500.f*Counter), 0.f, 0.f);
			FVector ForwardVe = FVector(500.f, 0.f, 0.f);
			FVector EndTr = (ForwardVe * 1 + StartTr);
			FCollisionQueryParams* TracePa = new FCollisionQueryParams();
			TracePa->bTraceComplex = false;
			FCollisionResponseParams ResponseParams(ECollisionResponse::ECR_Overlap);
			GetWorld()->LineTraceMultiByChannel(HitResults, StartTr, EndTr, ECC_Visibility, *TracePa, ResponseParams);
			if (GetWorld()->LineTraceSingleByChannel(HitResults[0], StartTr + FVector(500.f, 0.f, 0.f), EndTr + FVector(500.f, 0.f, 0.f), ECC_Visibility, *TracePa) == NULL)
			{
				break;
			}
			for (int x = 0; x != HitResults.Num(); ++x)
			{
				//SpareMove = MoveLimit - MoveFLimit;
				if (x == 0)
				{
					TArray<FHitResult> SHitResults;
					SHitResults.Init(FHitResult(ForceInit), 10);
					SCounter = 0;
					SpareMove = MoveFLimit;
					SpareStart = StartTr;
					SpareEnd = EndTr;
					do
					{
						//SpareStart = StartTr;
						//SpareEnd = EndTr;
						StartTr = SpareStart + SCounter * VLeft;
						EndTr = SpareStart + (SCounter + 1) * VLeft;
						GetWorld()->LineTraceMultiByChannel(SHitResults, StartTr, EndTr, ECC_Visibility, *TracePa, ResponseParams);
						if (GetWorld()->LineTraceSingleByChannel(SHitResults[0], StartTr + VLeft, EndTr + VLeft, ECC_Visibility, *TracePa) == NULL)
						{
							break;
						}
						for (int y = 0; y != SHitResults.Num(); ++y)
						{
							DrawDebugLine(GetWorld(), StartTr + FVector(0.f, 0.f, 500.f), EndTr + FVector(0.f, 0.f, 500.f), FColor::Blue, false, 5.f);
							if (y == 1)
							{
								//DrawDebugLine(GetWorld(), StartTr + FVector(0.f, 0.f, 500.f), EndTr + FVector(0.f, 0.f, 500.f), FColor::Blue, false, 5.f);
								AStaticMeshActor* Field = Cast<AStaticMeshActor>(SHitResults[y].Actor.Get());
								ATrawa* Trawaa = Cast<ATrawa>(SHitResults[y].Actor.Get());
								//GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString::Printf(TEXT("%f"), Trawaa->MPCost));
								if (Trawaa->MPCost <= MoveLimit - SpareMove)
									Trawaa->ChangeMaterial();
								SpareMove += Trawaa->MPCost;
								Tap[SCounter] = Trawaa->MPCost;
								SCounter++;
							}
						}
					} while (SpareMove < MoveLimit);
					//TArray<FHitResult> SHitResults;
					//SHitResults.Init(FHitResult(ForceInit), 10);
					SCounter = 0;
					SpareMove = MoveFLimit;
					StartTr = SpareStart;
					EndTr = SpareEnd;
					do
					{
						//SpareStart = StartTr;
						//SpareEnd = EndTr;
						StartTr = SpareStart + SCounter * VRight;
						EndTr = SpareStart + (SCounter + 1) * VRight;
						GetWorld()->LineTraceMultiByChannel(SHitResults, StartTr, EndTr, ECC_Visibility, *TracePa, ResponseParams);
						if (GetWorld()->LineTraceSingleByChannel(SHitResults[0], StartTr + VRight, EndTr + VRight, ECC_Visibility, *TracePa) == NULL)
						{
							break;
						}
						for (int y = 0; y != SHitResults.Num(); ++y)
						{
							DrawDebugLine(GetWorld(), StartTr + FVector(0.f, 0.f, 500.f), EndTr + FVector(0.f, 0.f, 500.f), FColor::Blue, false, 5.f);
							if (y == 1)
							{
								//DrawDebugLine(GetWorld(), StartTr + FVector(0.f, 0.f, 500.f), EndTr + FVector(0.f, 0.f, 500.f), FColor::Blue, false, 5.f);
								AStaticMeshActor* Field = Cast<AStaticMeshActor>(SHitResults[y].Actor.Get());
								ATrawa* Trawaa = Cast<ATrawa>(SHitResults[y].Actor.Get());
								//GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString::Printf(TEXT("%f"), Trawaa->MPCost));
								if (Trawaa->MPCost <= MoveLimit - SpareMove)
									Trawaa->ChangeMaterial();
								SpareMove += Trawaa->MPCost;
								Tap[SCounter] = Trawaa->MPCost;
								SCounter++;
							}
						}
					} while (SpareMove < MoveLimit);
				}
					StartTr = SpareStart;
					EndTr = SpareEnd;
					DrawDebugLine(GetWorld(), StartTr + FVector(0.f, 0.f, 500.f), EndTr + FVector(0.f, 0.f, 500.f), FColor::Blue, false, 5.f);
				if (x == 1)
				{
					//DrawDebugLine(GetWorld(), StartTr + FVector(0.f, 0.f, 500.f), EndTr + FVector(0.f, 0.f, 500.f), FColor::Blue, false, 5.f);
					AStaticMeshActor* Field = Cast<AStaticMeshActor>(HitResults[x].Actor.Get());
					ATrawa* Trawaa = Cast<ATrawa>(HitResults[x].Actor.Get());
					//GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString::Printf(TEXT("%f"), Trawaa->MPCost));
					if (Trawaa->MPCost <= MoveLimit - MoveFLimit)
						Trawaa->ChangeMaterial();
					MoveFLimit += Trawaa->MPCost;
					Tap[Counter] = Trawaa->MPCost;
					Counter++;
				}
			}
		} while (MoveFLimit < MoveLimit);
		//Counter = 0;
		/*FVector StartTr = GetActorLocation() - FVector(500.f* MoveLimit, 0.f, 500.f);
		FVector ForwardVe = FVector(500.f, 0.f, 0.f);
		FVector EndTr = ((ForwardVe * (MoveLimit*2)) + StartTr);
		FCollisionQueryParams* TracePa = new FCollisionQueryParams();
		TracePa->bTraceComplex = false;
		FCollisionResponseParams ResponseParams(ECollisionResponse::ECR_Overlap);
		GetWorld()->LineTraceMultiByChannel(HitResults, StartTr, EndTr, ECC_Visibility, *TracePa, ResponseParams);
		DrawDebugLine(GetWorld(), StartTr, EndTr, FColor::Red, false, 5.f);
		for (int x = 0; x != HitResults.Num(); ++x)
		{
			GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString::Printf(TEXT("gowno")));
			AStaticMeshActor* Field = Cast<AStaticMeshActor>(HitResults[x].Actor.Get());
			ATrawa* Trawaa = Cast<ATrawa>(HitResults[x].Actor.Get());
			Trawaa->ChangeMaterial();
		}*/
	}
	else 
	{
		if (TestTarget != NULL)
		{
			//GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString::Printf(TEXT("Itemmmmm")));
			TestTarget->MarkerDestroy();
		}
	}
	searching();
}

void ATank::DestroyTank()
{
	Destroy();
}

void ATank::Hitt()
{
	UWorld* const World = GetWorld();
	FVector ActorLocation = GetActorLocation();
	FRotator ActorRotation = GetActorRotation();
	//Roll = GetActorLocation().Roll;
	//Pitch = GetActorLocation().Pitch;
	//Yaw = GetActorLocation().Yaw;
	FVector SpawnLocation = ActorLocation + FVector(0, 0, 67);
	FRotator SpawnRotation = ActorRotation;
	FActorSpawnParameters SpawnParams;
	AActor* SpawnedActorRef = GetWorld()->SpawnActor<AActor>(ActorToSpawn, SpawnLocation, SpawnRotation, SpawnParams);
}
void ATank::TriggerEnter(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult)
{
	Health -= 10;
	GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString::Printf(TEXT("DUPA")));
	DamageTaken(10.f);
}
void ATank::searching()
{
	TArray<FHitResult> HitResults;
	HitResults.Init(FHitResult(ForceInit), 20);
	MoveFLimit = 0;
	Counter = 0;
	do
	{
		FVector StartTr = GetActorLocation() - FVector(0.f, 0.f, 500.f) + FVector(0.f + (500.f * Counter), 0.f, 0.f);
		FVector ForwardVe = FVector(500.f, 0.f, 0.f);
		FVector EndTr = (ForwardVe * 1 + StartTr);
		FCollisionQueryParams* TracePa = new FCollisionQueryParams();
		TracePa->bTraceComplex = false;
		FCollisionResponseParams ResponseParams(ECollisionResponse::ECR_Overlap);
		GetWorld()->LineTraceMultiByChannel(HitResults, StartTr, EndTr, ECC_Visibility, *TracePa, ResponseParams);
		if (GetWorld()->LineTraceSingleByChannel(HitResults[0], StartTr + FVector(500.f, 0.f, 0.f), EndTr + FVector(500.f, 0.f, 0.f), ECC_Visibility, *TracePa) == NULL)
		{
			break;
		}
		for (int x = 0; x != HitResults.Num(); ++x)
		{
			//SpareMove = MoveLimit - MoveFLimit;
			if (x == 0)
			{
				TArray<FHitResult> SHitResults;
				SHitResults.Init(FHitResult(ForceInit), 10);
				SCounter = 0;
				SpareMove = MoveFLimit;
				SpareStart = StartTr;
				SpareEnd = EndTr;
				do
				{
					//SpareStart = StartTr;
					//SpareEnd = EndTr;
					StartTr = SpareStart + SCounter * VLeft;
					EndTr = SpareStart + (SCounter + 1) * VLeft;
					GetWorld()->LineTraceMultiByChannel(SHitResults, StartTr, EndTr, ECC_Visibility, *TracePa, ResponseParams);
					if (GetWorld()->LineTraceSingleByChannel(SHitResults[0], StartTr + VLeft, EndTr + VLeft, ECC_Visibility, *TracePa) == NULL)
					{
						break;
					}
					for (int y = 0; y != SHitResults.Num(); ++y)
					{
						DrawDebugLine(GetWorld(), StartTr + FVector(0.f, 0.f, 500.f), EndTr + FVector(0.f, 0.f, 500.f), FColor::Blue, false, 5.f);
						if (y == 1)
						{
							//DrawDebugLine(GetWorld(), StartTr + FVector(0.f, 0.f, 500.f), EndTr + FVector(0.f, 0.f, 500.f), FColor::Blue, false, 5.f);
							AStaticMeshActor* Field = Cast<AStaticMeshActor>(SHitResults[y].Actor.Get());
							ATrawa* Trawaa = Cast<ATrawa>(SHitResults[y].Actor.Get());
							//GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString::Printf(TEXT("%f"), Trawaa->MPCost));
							if (Trawaa->MPCost <= MoveLimit - SpareMove)
								Trawaa->ChangeMaterial();
							SpareMove += Trawaa->MPCost;
							Tap[SCounter] = Trawaa->MPCost;
							SCounter++;
						}
					}
				} while (SpareMove < MoveLimit);
				//TArray<FHitResult> SHitResults;
				//SHitResults.Init(FHitResult(ForceInit), 10);
				SCounter = 0;
				SpareMove = MoveFLimit;
				StartTr = SpareStart;
				EndTr = SpareEnd;
				do
				{
					//SpareStart = StartTr;
					//SpareEnd = EndTr;
					StartTr = SpareStart + SCounter * VRight;
					EndTr = SpareStart + (SCounter + 1) * VRight;
					GetWorld()->LineTraceMultiByChannel(SHitResults, StartTr, EndTr, ECC_Visibility, *TracePa, ResponseParams);
					if (GetWorld()->LineTraceSingleByChannel(SHitResults[0], StartTr + VRight, EndTr + VRight, ECC_Visibility, *TracePa) == NULL)
					{
						break;
					}
					for (int y = 0; y != SHitResults.Num(); ++y)
					{
						DrawDebugLine(GetWorld(), StartTr + FVector(0.f, 0.f, 500.f), EndTr + FVector(0.f, 0.f, 500.f), FColor::Blue, false, 5.f);
						if (y == 1)
						{
							//DrawDebugLine(GetWorld(), StartTr + FVector(0.f, 0.f, 500.f), EndTr + FVector(0.f, 0.f, 500.f), FColor::Blue, false, 5.f);
							AStaticMeshActor* Field = Cast<AStaticMeshActor>(SHitResults[y].Actor.Get());
							ATrawa* Trawaa = Cast<ATrawa>(SHitResults[y].Actor.Get());
							//GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString::Printf(TEXT("%f"), Trawaa->MPCost));
							if (Trawaa->MPCost <= MoveLimit - SpareMove)
								Trawaa->ChangeMaterial();
							SpareMove += Trawaa->MPCost;
							Tap[SCounter] = Trawaa->MPCost;
							SCounter++;
						}
					}
				} while (SpareMove < MoveLimit);
			}
			StartTr = SpareStart;
			EndTr = SpareEnd;
			DrawDebugLine(GetWorld(), StartTr + FVector(0.f, 0.f, 500.f), EndTr + FVector(0.f, 0.f, 500.f), FColor::Blue, false, 5.f);
			if (x == 1)
			{
				//DrawDebugLine(GetWorld(), StartTr + FVector(0.f, 0.f, 500.f), EndTr + FVector(0.f, 0.f, 500.f), FColor::Blue, false, 5.f);
				AStaticMeshActor* Field = Cast<AStaticMeshActor>(HitResults[x].Actor.Get());
				ATrawa* Trawaa = Cast<ATrawa>(HitResults[x].Actor.Get());
				//GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString::Printf(TEXT("%f"), Trawaa->MPCost));
				if (Trawaa->MPCost <= MoveLimit - MoveFLimit)
					Trawaa->ChangeMaterial();
				MoveFLimit += Trawaa->MPCost;
				Tap[Counter] = Trawaa->MPCost;
				Counter++;
			}
		}
	} while (MoveFLimit < MoveLimit);


	MoveFLimit = 0;
	Counter = 0;
	do
	{
		FVector StartTr = GetActorLocation() - FVector(0.f, 0.f, 500.f) + FVector(0.f - (500.f * Counter), 0.f, 0.f);
		FVector ForwardVe = VBackward;
		FVector EndTr = (ForwardVe * 1 + StartTr);
		FCollisionQueryParams* TracePa = new FCollisionQueryParams();
		TracePa->bTraceComplex = false;
		FCollisionResponseParams ResponseParams(ECollisionResponse::ECR_Overlap);
		GetWorld()->LineTraceMultiByChannel(HitResults, StartTr, EndTr, ECC_Visibility, *TracePa, ResponseParams);
		if (GetWorld()->LineTraceSingleByChannel(HitResults[0], StartTr + VBackward, EndTr + VBackward, ECC_Visibility, *TracePa) == NULL)
		{
			break;
		}
		for (int x = 0; x != HitResults.Num(); ++x)
		{
			//SpareMove = MoveLimit - MoveFLimit;
			if (x == 0)
			{
				TArray<FHitResult> SHitResults;
				SHitResults.Init(FHitResult(ForceInit), 10);
				SCounter = 0;
				SpareMove = MoveFLimit;
				SpareStart = StartTr;
				SpareEnd = EndTr;
				do
				{
					//SpareStart = StartTr;
					//SpareEnd = EndTr;
					StartTr = SpareStart + SCounter * VLeft;
					EndTr = SpareStart + (SCounter + 1) * VLeft;
					GetWorld()->LineTraceMultiByChannel(SHitResults, StartTr, EndTr, ECC_Visibility, *TracePa, ResponseParams);
					if (GetWorld()->LineTraceSingleByChannel(SHitResults[0], StartTr + VLeft, EndTr + VLeft, ECC_Visibility, *TracePa) == NULL)
					{
						break;
					}
					for (int y = 0; y != SHitResults.Num(); ++y)
					{
						DrawDebugLine(GetWorld(), StartTr + FVector(0.f, 0.f, 500.f), EndTr + FVector(0.f, 0.f, 500.f), FColor::Blue, false, 5.f);
						if (y == 1)
						{
							//DrawDebugLine(GetWorld(), StartTr + FVector(0.f, 0.f, 500.f), EndTr + FVector(0.f, 0.f, 500.f), FColor::Blue, false, 5.f);
							AStaticMeshActor* Field = Cast<AStaticMeshActor>(SHitResults[y].Actor.Get());
							ATrawa* Trawaa = Cast<ATrawa>(SHitResults[y].Actor.Get());
							//GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString::Printf(TEXT("%f"), Trawaa->MPCost));
							if (Trawaa->MPCost <= MoveLimit - SpareMove)
								Trawaa->ChangeMaterial();
							SpareMove += Trawaa->MPCost;
							Tap[SCounter] = Trawaa->MPCost;
							SCounter++;
						}
					}
				} while (SpareMove < MoveLimit);
				//TArray<FHitResult> SHitResults;
				//SHitResults.Init(FHitResult(ForceInit), 10);
				SCounter = 0;
				SpareMove = MoveFLimit;
				StartTr = SpareStart;
				EndTr = SpareEnd;
				do
				{
					//SpareStart = StartTr;
					//SpareEnd = EndTr;
					StartTr = SpareStart + SCounter * VRight;
					EndTr = SpareStart + (SCounter + 1) * VRight;
					GetWorld()->LineTraceMultiByChannel(SHitResults, StartTr, EndTr, ECC_Visibility, *TracePa, ResponseParams);
					if (GetWorld()->LineTraceSingleByChannel(SHitResults[0], StartTr + VRight, EndTr + VRight, ECC_Visibility, *TracePa) == NULL)
					{
						break;
					}
					for (int y = 0; y != SHitResults.Num(); ++y)
					{
						DrawDebugLine(GetWorld(), StartTr + FVector(0.f, 0.f, 500.f), EndTr + FVector(0.f, 0.f, 500.f), FColor::Blue, false, 5.f);
						if (y == 1)
						{
							//DrawDebugLine(GetWorld(), StartTr + FVector(0.f, 0.f, 500.f), EndTr + FVector(0.f, 0.f, 500.f), FColor::Blue, false, 5.f);
							AStaticMeshActor* Field = Cast<AStaticMeshActor>(SHitResults[y].Actor.Get());
							ATrawa* Trawaa = Cast<ATrawa>(SHitResults[y].Actor.Get());
							//GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString::Printf(TEXT("%f"), Trawaa->MPCost));
							if (Trawaa->MPCost <= MoveLimit - SpareMove)
								Trawaa->ChangeMaterial();
							SpareMove += Trawaa->MPCost;
							Tap[SCounter] = Trawaa->MPCost;
							SCounter++;
						}
					}
				} while (SpareMove < MoveLimit);
			}
			StartTr = SpareStart;
			EndTr = SpareEnd;
			DrawDebugLine(GetWorld(), StartTr + FVector(0.f, 0.f, 500.f), EndTr + FVector(0.f, 0.f, 500.f), FColor::Blue, false, 5.f);
			if (x == 1)
			{
				//DrawDebugLine(GetWorld(), StartTr + FVector(0.f, 0.f, 500.f), EndTr + FVector(0.f, 0.f, 500.f), FColor::Blue, false, 5.f);
				AStaticMeshActor* Field = Cast<AStaticMeshActor>(HitResults[x].Actor.Get());
				ATrawa* Trawaa = Cast<ATrawa>(HitResults[x].Actor.Get());
				//GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString::Printf(TEXT("%f"), Trawaa->MPCost));
				if (Trawaa->MPCost <= MoveLimit - MoveFLimit)
					Trawaa->ChangeMaterial();
				MoveFLimit += Trawaa->MPCost;
				Tap[Counter] = Trawaa->MPCost;
				Counter++;
			}
		}
	} while (MoveFLimit < MoveLimit);
}
//void ATank::TriggerExit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
//{
//}
void ATank::Text()
{
	//FVector lolL = GetActorLocation();
	//lolL = lolL + (0, 0, 180.f);
	ADwaCharacter* Character = Cast< ADwaCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	FRotator lol = Character->GetActorRotation();
	lol.Yaw += 180.f;
	//lolL = lolL + (0, 0, 180.f);
	HealthText->SetRelativeRotation(lol);
	//HealthText->SetRelativeLocation(lolL);
}
void ATank::TMove(float Axis, bool sign)
{
	
	Actor = GetActorLocation();
	New = GetActorLocation();
	//if (-0.5 < MoveLimit)
	//{
		if (Axis == 1 && sign == false)
		{
			FHitResult* HitR = new FHitResult();
			FVector StartT = GetActorLocation();
			FVector ForwardV = FVector(-1.f, 0.f, 0.f);
			FVector EndT = ((ForwardV * 500.f) + StartT);
			FCollisionQueryParams TraceP;
			TraceP.AddIgnoredActor(this);
			if (GetWorld()->LineTraceSingleByChannel(*HitR, StartT, EndT, ECC_Visibility, TraceP)==NULL)
				Empty = true;
			if (Empty == true)  MoveLimit -= Tap[0];
			TAxis = 1;
			Tsign = false;
			//FVector ActorLocation = GetActorLocation();
			//FVector NewLocation = ActorLocation + FVector(-forward, 0.f, 0.f);
			NewRotation = GetActorRotation();
			rot = NewRotation.Yaw;
			//if (rot != -90.f && rot < -100.f || rot != -90.f && rot > -80.f)
			Forward = false;
			//else
			//{
				//FVector ActorLocation = GetActorLocation();
				//FVector NewLocation = ActorLocation + FVector(-forward, 0.f, 0.f);
				//SetActorLocation(NewLocation);
			TestTarget->MMove(Axis, -forward);
			//}
			Move = true;
			//SetActorLocation(NewLocation);
			//TestTarget->MMove(Axis, -forward);
		}
		else if (Axis == 1 && sign == true)
		{
			FHitResult* HitR = new FHitResult();
			FVector StartT = GetActorLocation();
			FVector ForwardV = FVector(1.f, 0.f, 0.f);
			FVector EndT = ((ForwardV * 500.f) + StartT);
			FCollisionQueryParams TraceP;
			TraceP.AddIgnoredActor(this);
			if (GetWorld()->LineTraceSingleByChannel(*HitR, StartT, EndT, ECC_Visibility, TraceP) == NULL)
				Empty = true;
			if (Empty == true)  MoveLimit -= Tap[0];
				TAxis = 1;
				Tsign = true;
				//FVector ActorLocation = GetActorLocation();
				//FVector NewLocation = ActorLocation + FVector(forward, 0.f, 0.f);
				NewRotation = GetActorRotation();
				rot = NewRotation.Yaw;
				//if (rot != 90.f && rot < 80.f || rot != 90.f && rot > 100.f)
				Backward = false;
				//else
				//{
					//FVector ActorLocation = GetActorLocation();
					//FVector NewLocation = ActorLocation + FVector(forward, 0.f, 0.f);
					//SetActorLocation(NewLocation);
				TestTarget->MMove(Axis, forward);
				//}
				//SetActorLocation(NewLocation);
				//TestTarget->MMove(Axis, forward);
				Move = true;
		}
		else if (Axis == 2 && sign == false)
		{
			FHitResult* HitR = new FHitResult();
			FVector StartT = GetActorLocation();
			FVector ForwardV = FVector(0.f, -1.f, 0.f);
			FVector EndT = ((ForwardV * 500.f) + StartT);
			FCollisionQueryParams TraceP;
			TraceP.AddIgnoredActor(this);
			if (GetWorld()->LineTraceSingleByChannel(*HitR, StartT, EndT, ECC_Visibility, TraceP) == NULL)
				Empty = true;
			if (Empty == true)  MoveLimit -= Tap[0];
				TAxis = 2;
				Tsign = false;
				//FVector ActorLocation = GetActorLocation();
				//FVector NewLocation = ActorLocation + FVector(0.f, -forward, 0.f);
				NewRotation = GetActorRotation();
				rot = NewRotation.Yaw;
				//if (rot != 0.f && rot < -10.f || rot != 0.f && rot > 10.f)
				Right = false;
				//else
				//{
					//FVector ActorLocation = GetActorLocation();
					//FVector NewLocation = ActorLocation + FVector(0.f, -forward, 0.f);
					//SetActorLocation(NewLocation);
				TestTarget->MMove(Axis, -forward);
				//}
				//SetActorLocation(NewLocation);
				//TestTarget->MMove(Axis, -forward);
				Move = true;

		}
		else if (Axis == 2 && sign == true)
		{
			FHitResult* HitR = new FHitResult();
			FVector StartT = GetActorLocation();
			FVector ForwardV = FVector(0.f, 1.f, 0.f);
			FVector EndT = ((ForwardV * 500.f) + StartT);
			FCollisionQueryParams TraceP;
			TraceP.AddIgnoredActor(this);
			if (GetWorld()->LineTraceSingleByChannel(*HitR, StartT, EndT, ECC_Visibility, TraceP) == NULL)
				Empty = true;
			if (Empty == true)  MoveLimit -= Tap[0];
			TAxis = 2;
			Tsign = true;
			//FVector ActorLocation = GetActorLocation();
			//FVector NewLocation = ActorLocation + FVector(0.f, forward, 0.f);
			NewRotation = GetActorRotation();
			rot = NewRotation.Yaw;
			//if (rot != 179.f && rot < 170.f || rot != 179.f && rot > - 170.f)
			Left = false;
			//else
			//{
				//FVector ActorLocation = GetActorLocation();
				//FVector NewLocation = ActorLocation + FVector(0.f, forward, 0.f);
				//SetActorLocation(NewLocation);
			TestTarget->MMove(Axis, forward);
			//}
			//NewRotation = FRotator(0.f, 180.f, 0.f);
			//SetActorRotation(NewRotation);
			Move = true;
			//SetActorLocation(NewLocation);
			//TestTarget->MMove(Axis, forward);
			//for (rot; 90 > rot; rot++)
			//Tick(1.f);
		}
	//}
}	
void ATank::TTMoveL(float Axis, bool sign)
{
	if (Left == true && Move == true)
	{
		//GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString::Printf(TEXT("Left")));
		//FVector ActorLocation = GetActorLocation();
		//FVector NewLocation = ActorLocation + FVector(0.f, forward, 0.f);
		//SetActorLocation(NewLocation);
		TestTarget->MMove(Axis, forward);
		Move = false;
	}
}
void ATank::TTMoveF(float Axis, bool sign)
{
	if (Forward == true && Move == true)
	{
		//GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString::Printf(TEXT("Forward")));
		//FVector ActorLocation = GetActorLocation();
		//FVector NewLocation = ActorLocation + FVector(-forward, 0.f, 0.f);
		//SetActorLocation(NewLocation);
		TestTarget->MMove(Axis, -forward);
		Move = false;
	}
}
void ATank::TTMoveR(float Axis, bool sign)
{
	if (Right == true && Move == true)
	{
		//GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString::Printf(TEXT("Right")));
		//FVector ActorLocation = GetActorLocation();
		//FVector NewLocation = ActorLocation + FVector(0.f, -forward, 0.f);
		//SetActorLocation(NewLocation);
		TestTarget->MMove(Axis, -forward);
		Move = false;
	}
}
void ATank::TTMoveB(float Axis, bool sign)
{
	if (Backward == true && Move == true)
	{
		//GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString::Printf(TEXT("Backward")));
		//FVector ActorLocation = GetActorLocation();
		//FVector NewLocation = ActorLocation + FVector(forward, 0.f, 0.f);
		//SetActorLocation(NewLocation);
		TestTarget->MMove(Axis, forward);
		Move = false;
	}
}

/*int ATank::Mod(float one, float two)
{
	int a = two / one;
	int b = a * one;
	int c = two - b;
	return c;
}*/

