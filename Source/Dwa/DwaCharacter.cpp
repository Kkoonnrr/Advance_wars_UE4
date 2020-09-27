// Copyright Epic Games, Inc. All Rights Reserved.

#include "DwaCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine.h"
#include "Tank.h"
#include "Factoryy.h"
#include "Engine/World.h"
//////////////////////////////////////////////////////////////////////////
// ADwaCharacter

ADwaCharacter::ADwaCharacter()
{
	/*FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;*/
	//Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;
	Choosen = false;
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void ADwaCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("ObjUp", IE_Released, this, &ADwaCharacter::ObjUp);
	PlayerInputComponent->BindAction("ObjDown", IE_Released, this, &ADwaCharacter::ObjDown);
	PlayerInputComponent->BindAction("ObjRight", IE_Released, this, &ADwaCharacter::ObjRight);
	PlayerInputComponent->BindAction("ObjLeft", IE_Released, this, &ADwaCharacter::ObjLeft);

	PlayerInputComponent->BindAxis("MoveForward", this, &ADwaCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADwaCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ADwaCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ADwaCharacter::LookUpAtRate);
	PlayerInputComponent->BindAxis("MoveUp", this, &ADwaCharacter::MoveUp);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ADwaCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ADwaCharacter::TouchStopped);

	PlayerInputComponent->BindAction("Pickup", IE_Pressed, this, &ADwaCharacter::BeginPickup);
	PlayerInputComponent->BindAction("Pickup", IE_Released, this, &ADwaCharacter::EndPickup);
	PlayerInputComponent->BindAction("ShowInventory", IE_Pressed, this, &ADwaCharacter::ShowInventory);
	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ADwaCharacter::OnResetVR);
	PlayerInputComponent->BindAction("Hit", IE_Pressed, this, &ADwaCharacter::Hit);
}

void ADwaCharacter::Hit()
{

	FHitResult* HitResult = new FHitResult();
	FVector StartTrace = FollowCamera->GetComponentLocation();
	FVector ForwardVector = FollowCamera->GetForwardVector();
	FVector EndTrace = ((ForwardVector * 2000.f) + StartTrace);
	FCollisionQueryParams* TraceParams = new FCollisionQueryParams();
	if (GetWorld()->LineTraceSingleByChannel(*HitResult, StartTrace, EndTrace, ECC_Visibility, *TraceParams))
	{
		DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Green, false, 5.f);
		if (Cast<AFactoryy>(HitResult->Actor.Get()) != NULL)
		{
			Factory = Cast<AFactoryy>(HitResult->Actor.Get());
			GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString::Printf(TEXT("APUD")));
			Factory->Create = true;
			Factory->CreateTank();
		}
		if (TestTarget == NULL || Choosen == false)
			TestTarget = Cast<ATank>(HitResult->Actor.Get());
		else
			TestTargetFalse = Cast<ATank>(HitResult->Actor.Get());
		if (TestTargetFalse == TestTarget) TestTargetFalse = NULL;
		if (TestTarget != NULL && !TestTarget->IsPendingKill() && Choosen == false && TestTarget->Choosen == false)
		{
			//TestTarget->DamageTaken(10.f);
			TestTarget->Hitt();
			TestTarget->Choosen = true;
			TestTarget->Choice(TestTarget->Choosen);
			Choosen = true;
		}
		else if (TestTargetFalse == NULL &&TestTarget != NULL && !TestTarget->IsPendingKill() && Choosen == true && TestTarget->Choosen == true)
		{
			TestTarget->Hitt();
			TestTarget->Choosen = false;
			TestTarget->Choice(TestTarget->Choosen);
			Choosen = false;
		}
		if (TestTargetFalse != NULL && TestTarget != NULL && !TestTarget->IsPendingKill() && Choosen == true && TestTarget->Choosen == true)
		{
			TestTargetFalse->Hitt();
			TestTargetFalse->Choosen = true;
			TestTargetFalse->Choice(TestTarget->Choosen);
			TestTarget->Hitt();
			TestTarget->Choosen = false;
			TestTarget->Choice(TestTarget->Choosen);
			TestTarget = TestTargetFalse;
			TestTargetFalse = NULL;
		}

	}
}


void ADwaCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ADwaCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void ADwaCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void ADwaCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ADwaCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ADwaCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ADwaCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
void ADwaCharacter::MoveUp(float value)
{
	if ((Controller != NULL) && (value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Z);
		AddMovementInput(Direction, value);
	}
}

void ADwaCharacter::BeginPickup()
{
	BIsPickingUp = true;
}
void ADwaCharacter::EndPickup()
{
	BIsPickingUp = false;
}
void ADwaCharacter::ShowInventory()
{
	for (auto& something : Inventory)
	{
		GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString::Printf(TEXT("Item: %s"), *something));
	}
}
void ADwaCharacter::ObjUp()
{
	if (Choosen == true)
	{
		if (TestTarget->Choosen == true)
		{
			TestTarget->TMove(1, false);
		}
	}
}
void ADwaCharacter::ObjDown()
{
	if (Choosen == true)
	{
		if (TestTarget->Choosen == true)
		{
			TestTarget->TMove(1, true);
		}
	}
}
void ADwaCharacter::ObjRight()
{
	if (Choosen == true)
	{
		if (TestTarget->Choosen == true)
		{
			TestTarget->TMove(2, false);
		}
	}
}
void ADwaCharacter::ObjLeft()
{
	if (Choosen == true)
	{
		if (TestTarget->Choosen == true)
		{
			TestTarget->TMove(2, true);
		}
	}
}