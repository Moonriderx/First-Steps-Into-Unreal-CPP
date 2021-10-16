// Fill out your copyright notice in the Description page of Project Settings.


#include "ThirdPersonController.h"

// Sets default values
AThirdPersonController::AThirdPersonController()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f); // capsule half height and the radius

	bUseControllerRotationPitch = false; // this is going to forbid the controller to rotate from the controller
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true; // it will allow the character to rotate in the direction where it is moving
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // this is the rotation rate. (how much we will be going to rotate)
	GetCharacterMovement()->JumpZVelocity = 600.0f; // our jump velocity its going to be 600;
	GetCharacterMovement()->AirControl = 0.2f; // air control

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent); // attach it to the capsule (child of the capsule)

	CameraBoom->TargetArmLength = 300.0f; // how far the springArm will going to be away from the player
	CameraBoom->bUsePawnControlRotation = true; // rotate the arm based on the controller

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // this is going to attach the camera at the end of the boom

	FollowCamera->bUsePawnControlRotation = false;


}

// Called when the game starts or when spawned
void AThirdPersonController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AThirdPersonController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AThirdPersonController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

