// Fill out your copyright notice in the Description page of Project Settings.


#include "GridSystem.h"

#include "Constants.h"
#include "GridCell.h"
#include "TurnBased/Algorithms/Pathfinding/AStar/AStarAlgorithm.h"

// Sets default values
AGridSystem::AGridSystem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGridSystem::BeginPlay()
{
	Super::BeginPlay();
	CreateGrids(FVector2D(0, 0), 10, 10);
	AStar = GetWorld()->SpawnActor<AStarAlgorithm>();	
	GridCells[1]->SetIsAvailable(false);
	GridCells[12]->SetIsAvailable(false);
	GridCells[22]->SetIsAvailable(false);
	GridCells[32]->SetIsAvailable(false);
	TArray<AGridCell*> Path = AStar->AStarSearch(this , GridCells[0] , GridCells.Last());

	for (auto GridCell : Path)
	{
		GridCell->SetActorLocation(GridCell->GetActorLocation() + FVector(0,0,50));
	}

	AStar->Destroy();
	
}

// Called every frame
void AGridSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGridSystem::CreateGrids(FVector2D StartPos, int Row, int Column)
{
	if (StartPos.X == 0 && StartPos.Y == 0)
	{
		StartPos = FVector2D(GetActorLocation().X, GetActorLocation().Y);
	}

	SystemStartPosition = StartPos;
	SystemRow = Row;
	SystemColumn = Column;

	for (int h = 0; h < Row; h++)
	{
		for (int w = 0; w < Column; w++)
		{
			FVector PlacementPos = FVector(StartPos.X + w * Grid::FConstants::FGridSettings::HorizontalGridSize,
			                               StartPos.Y + h * Grid::FConstants::FGridSettings::VerticalGridSpace, 0);
			AGridCell* GridCell = GetWorld()->SpawnActor<AGridCell>(BP_GridCell, PlacementPos, GetActorRotation());
			GridCell->SetActorLocation(FVector(PlacementPos.X, PlacementPos.Y, 0));
			GridCell->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
			GridCell->SetCoord(h, w);
			GridCells.Add(GridCell);
		}
	}

	SetNeighbors();
}

void AGridSystem::SetNeighbors()
{
	for (AGridCell* Element : GridCells)
	{
		FVector2d ElementCoord = Element->GetCoord();
		Element->SetNeighbor(EGridNeighborDirections::East,
		                     FindGridByCoord(FVector2D(ElementCoord.X + Grid::FConstants::FDirections::East.X,
		                                               ElementCoord.Y + Grid::FConstants::FDirections::East.Y)));
		Element->SetNeighbor(EGridNeighborDirections::West,
		                     FindGridByCoord(FVector2D(ElementCoord.X + Grid::FConstants::FDirections::West.X,
		                                               ElementCoord.Y + Grid::FConstants::FDirections::West.Y)));
		Element->SetNeighbor(EGridNeighborDirections::North,
		                     FindGridByCoord(FVector2D(ElementCoord.X + Grid::FConstants::FDirections::North.X,
		                                               ElementCoord.Y + Grid::FConstants::FDirections::North.Y)));
		Element->SetNeighbor(EGridNeighborDirections::South,
		                     FindGridByCoord(FVector2D(ElementCoord.X + Grid::FConstants::FDirections::South.X,
		                                               ElementCoord.Y + Grid::FConstants::FDirections::South.Y)));
	}
}

void AGridSystem::PlaceAnActor(AGridActor* Actor, FVector2D Coord)
{
	AGridCell* GridCell = FindGridByCoord(Coord);

	Actor->SetGridCellUnderActor(GridCell);
	Actor->SetActorLocation(GridCell->GetActorLocation());

	GridCell->SetPlacedActor(Actor);
	GridCell->SetIsAvailable(false);
}


AGridCell* AGridSystem::FindGridByCoord(const FVector2D Coord)
{
	for (AGridCell* Element : GridCells)
	{
		FVector2D ElementCoord = Element->GetCoord();
		if (ElementCoord.X == Coord.X && ElementCoord.Y == Coord.Y)
		{
			return Element;
		}
	}
	return nullptr;
}
