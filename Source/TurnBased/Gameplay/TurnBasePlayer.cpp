// Fill out your copyright notice in the Description page of Project Settings.


#include "TurnBasePlayer.h"

#include "SkeletalDebugRendering.h"
#include "Engine/StaticMeshActor.h"
#include "TurnBased/Systems/Grid/GridSystem.h"


// Sets default values
ATurnBasePlayer::ATurnBasePlayer()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATurnBasePlayer::BeginPlay()
{
	Super::BeginPlay();

	UGridSystem* GridSystem = GetGameInstance()->GetSubsystem<UGridSystem>();
	GridSystem->CreateGrids(GridCell, FVector2D(0, 0), 10, 10);
	AGridActor* TestObs1 = GetWorld()->SpawnActor<AGridActor>(TestGridObstacle);
	GridSystem->PlaceAnActor(TestObs1, FVector2D(1, 1));
	AGridActor* TestObs2 = GetWorld()->SpawnActor<AGridActor>(TestGridObstacle);
	GridSystem->PlaceAnActor(TestObs2, FVector2D(2, 1));
	AGridActor* TestObs3 = GetWorld()->SpawnActor<AGridActor>(TestGridObstacle);
	GridSystem->PlaceAnActor(TestObs3, FVector2D(3, 1));
	AGridActor* TestObs4 = GetWorld()->SpawnActor<AGridActor>(TestGridObstacle);
	GridSystem->PlaceAnActor(TestObs4, FVector2D(5, 1));

	AGridActor* TestActor = GetWorld()->SpawnActor<AGridActor>(TestPlacementActor);
	
	GridSystem->PlaceAnActor(TestActor, FVector2D(0, 0));

	AGridActor* TestActor2 = GetWorld()->SpawnActor<AGridActor>(TestPlacementActor);
	
	GridSystem->PlaceAnActor(TestActor2, FVector2D(5, 5));
	
	//SelectedActor = TestActor;
}

// Called every frame
void ATurnBasePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATurnBasePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}