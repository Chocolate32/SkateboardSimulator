// Fill out your copyright notice in the Description page of Project Settings.


#include "SkateCharacter.h"

// Sets default values
ASkateCharacter::ASkateCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Camera
	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Arm"));
	CameraArm->SetupAttachment(RootComponent);
	CameraArm->TargetArmLength = TargetArmLength;
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraArm);

	//bUseControllerRotationPitch = false;
	//bUseControllerRotationYaw = false;
	//bUseControllerRotationRoll = false;

	//Mesh
	SkateMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Skate Mesh"));
	SkateMesh->SetupAttachment(RootComponent);

	//Character
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->BrakingDecelerationWalking = 2.f;
	GetCharacterMovement()->GroundFriction = .2f;

}

// Called when the game starts or when spawned
void ASkateCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Bind Imput Mapping Context
	if (APlayerController* MyController = Cast<APlayerController>(Controller)) {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(MyController->GetLocalPlayer())) {
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
}

void ASkateCharacter::MoveForward(const FInputActionValue& val)
{
	if (Controller) {
		float axis = val.Get<float>();

		FVector direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
		AddMovementInput(direction, axis);

		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("hello"));

	}
}

void ASkateCharacter::Turn(const FInputActionValue& val)
{
	if (Controller) {
		float axis = val.Get<float>();

		AddControllerYawInput(axis/5.0f);
		//AddActorWorldRotation(FRotator(0.f,axis,0.f));
		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("Value of axis = %f"), axis));
	}
}

void ASkateCharacter::Look(const FInputActionValue& val)
{
	if (Controller) {
		FVector2D lookV2 = val.Get<FVector2D>();


		FRotator camArmRot = CameraArm->GetRelativeRotation();
		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, camArmRot.ToString());
		camArmRot.Yaw += lookV2.X;
		float pitch = lookV2.Y + camArmRot.Pitch;
		camArmRot.Pitch = FMath::Clamp(pitch, -50.f, 30.f);

		CameraArm->SetRelativeRotation(camArmRot);
	}
}

// Called every frame
void ASkateCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASkateCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Input
	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		EnhancedInput->BindAction(Action_MoveForward, ETriggerEvent::Triggered, this, &ASkateCharacter::MoveForward);

		EnhancedInput->BindAction(Action_Turn, ETriggerEvent::Triggered, this, &ASkateCharacter::Turn);

		EnhancedInput->BindAction(Action_Look, ETriggerEvent::Triggered, this, &ASkateCharacter::Look);

		EnhancedInput->BindAction(Action_Jump, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInput->BindAction(Action_Jump, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	}
}

