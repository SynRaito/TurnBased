// Fill out your copyright notice in the Description page of Project Settings.


#include "GridCell.h"

// Sets default values
AGridCell::AGridCell()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGridCell::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGridCell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AGridCell::GetIsAvailable()
{
	return bIsAvailable;
}

void AGridCell::SetIsAvailable(bool State)
{
	bIsAvailable = State;
}

FVector2d AGridCell::GetCoord()
{
	return Coord;
}

void AGridCell::SetCoord(FVector2D C)
{
	Coord = C;
}

void AGridCell::SetCoord(int X, int Y)
{
	Coord = FVector2D(X,Y);
}

AActor* AGridCell::GetPlacedActor()
{
	return PlacedActor;
}

void AGridCell::SetPlacedActor(AActor* Actor)
{
	PlacedActor = Actor;
}

const AGridCell* AGridCell::GetNeighbor(EGridNeighborDirections Direction)
{
	switch (Direction)
	{
	case EGridNeighborDirections::North: return North;
	case EGridNeighborDirections::East: return East;
	case EGridNeighborDirections::South: return South;
	case EGridNeighborDirections::West: return West;
	default: return nullptr;
	}
}

void AGridCell::SetNeighbor(EGridNeighborDirections Direction, AGridCell* GridCell)
{
	switch (Direction)
	{
	case EGridNeighborDirections::North:
		North = GridCell;
		break;
	case EGridNeighborDirections::East:
		East = GridCell;
		break;
	case EGridNeighborDirections::South:
		South = GridCell;
		break;
	case EGridNeighborDirections::West:
		West = GridCell;
		break;
	}
}
