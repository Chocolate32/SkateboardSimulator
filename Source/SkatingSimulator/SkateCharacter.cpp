// Fill out your copyright notice in the Description page of Project Settings.


#include "SkateCharacter.h"

// Sets default values
ASkateCharacter::ASkateCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Arm"));
	CameraArm->SetupAttachment(RootComponent);
	CameraArm->TargetArmLength = TargetArmLength;
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraArm);

	SkateMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Skate Mesh"));
	SkateMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ASkateCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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

}

