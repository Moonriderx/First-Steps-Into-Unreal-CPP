// Fill out your copyright notice in the Description page of Project Settings.


#include "ThirdPerson_GameMode.h"
#include "GameFramework/Actor.h"

// this will going to determine what player to spawn (this GameMode)
AThirdPerson_GameMode::AThirdPerson_GameMode() {

	PrimaryActorTick.bCanEverTick = true;

}

void AThirdPerson_GameMode::BeginPlay() {

	Super::BeginPlay();

	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(UnusedHandle, this, &AThirdPerson_GameMode::SpawnPlayerRecharge, FMath::RandRange(2, 4), true);

}

void AThirdPerson_GameMode::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	
}

void AThirdPerson_GameMode::SpawnPlayerRecharge()
{
	float RandX = FMath::RandRange(Spawn_X_Min, Spawn_X_Max);
	float RandY = FMath::RandRange(Spawn_Y_Min, Spawn_Y_Max);

	FVector SpawnPosition = FVector(RandX, RandY, Spawn_Z);
	FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);

	GetWorld()->SpawnActor(PlayerRecharge, &SpawnPosition, &SpawnRotation);


}
