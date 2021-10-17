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

	bDead = false;



}





// Called when the game starts or when spawned
void AThirdPersonController::BeginPlay()
{
	Super::BeginPlay();

	

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AThirdPersonController::OnBeginOverlap); 
	
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

	//bind the mouse
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);


	PlayerInputComponent->BindAxis("MoveForward", this, &AThirdPersonController::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AThirdPersonController::MoveRight);
	

}

void AThirdPersonController::MoveForward(float Axis)
{

	if (!bDead) {
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X); // calculate the forward direction of YawRotation vector
		AddMovementInput(Direction, Axis);
	}

}

void AThirdPersonController::MoveRight(float Axis)
{
	if (!bDead) {
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y); // calculate the forward direction of YawRotation vector
		AddMovementInput(Direction, Axis);
	}

}

void AThirdPersonController::OnBeginOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComponent, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (OtherActor->ActorHasTag("Recharge")) { // if the collided object has tag Recharge
		UE_LOG(LogTemp, Warning, TEXT("Collided with")); 
	}


}

