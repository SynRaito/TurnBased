// Fill out your copyright notice in the Description page of Project Settings.


#include "TurnBasePlayer.h"

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
	GridSystem->GridCells[1]->SetIsAvailable(false);
	GridSystem->GridCells[12]->SetIsAvailable(false);
	GridSystem->GridCells[22]->SetIsAvailable(false);
	GridSystem->GridCells[32]->SetIsAvailable(false);

	AGridActor* TestActor = GetWorld()->SpawnActor<AGridActor>(TestPlacementActor);
	
	GridSystem->PlaceAnActor(TestActor, FVector2D(0, 0));
	
	SelectedActor = TestActor;
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

void ATurnBasePlayer::TestRandomMove()
{
	UGridSystem* GridSystem = GetGameInstance()->GetSubsystem<UGridSystem>();

	int Random = FMath::RandRange(0,GridSystem->GridCells.Num() - 1);
	
	GridSystem->MoveAnActor(SelectedActor, GridSystem->GridCells[Random]);
}