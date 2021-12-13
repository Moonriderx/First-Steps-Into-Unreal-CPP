// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSBombActor.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "Components/PrimitiveComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

// Sets default values
AFPSBombActor::AFPSBombActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ExplodeDelay = 2.0f;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp")); // we need to create an instance otherwise the meshcomp will be empty
	RootComponent = MeshComp;

}

void AFPSBombActor::Explode()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, ExplosionTemplate, GetActorLocation());

	TArray<FOverlapResult> OutOverLaps;

	FCollisionObjectQueryParams QueryParams;

	FCollisionShape CollShape;
	CollShape.SetSphere(500.0f);

	QueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	GetWorld()->OverlapMultiByObjectType(OutOverLaps, GetActorLocation(), FQuat::Identity, QueryParams, CollShape); // we will get a list of overlap results, FQuat::Identity means no rotated

	for (FOverlapResult Result : OutOverLaps) 
	{
		UPrimitiveComponent* Overlap = Result.GetComponent();
		if (Overlap && Overlap->IsSimulatingPhysics()) 
		{
			UMaterialInstanceDynamic* MatInst = Overlap->CreateAndSetMaterialInstanceDynamic(0);

			if (MatInst) 
			{
				MatInst->SetVectorParameterValue("DiffuseColor", TargetColor);
			}
		}
	}

	Destroy();
}

// Called when the game starts or when spawned
void AFPSBombActor::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle Explode_TimerHandle;

	GetWorldTimerManager().SetTimer(Explode_TimerHandle, this, &AFPSBombActor::Explode, ExplodeDelay);

	MaterialInst = MeshComp->CreateAndSetMaterialInstanceDynamic(0);

	if (MaterialInst) 
	{
		CurrentColor = MaterialInst->K2_GetVectorParameterValue("DiffuseColor");
	}

	TargetColor = FLinearColor::MakeRandomColor();
	
}

// Called every frame
void AFPSBombActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MaterialInst) 
	{
		float Progress = (GetWorld()->TimeSeconds - CreationTime) / ExplodeDelay; // amount of seconds that we are alive

		FLinearColor NewColor = FLinearColor::LerpUsingHSV(CurrentColor, TargetColor, Progress);

		MaterialInst->SetVectorParameterValue("DiffuseColor", NewColor);
	}

}

