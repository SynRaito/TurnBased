// Fill out your copyright notice in the Description page of Project Settings.

#include "GridSystem.h"

#include <functional>

#include "Constants.h"
#include "GridCell.h"
#include "Components/GridMovement.h"
#include "TurnBased/Algorithms/Pathfinding/AStar/AStarAlgorithm.h"
#include "TurnBased/Utilities/TimeManagement/Coroutine/CoroutineManager.h"


void UGridSystem::CreateGrids(TSubclassOf<AGridCell> BP_GridCell,FVector2D StartPos, int Row, int Column)
{
	if (StartPos.X == 0 && StartPos.Y == 0)
	{
		StartPos = FVector2D(0,0);
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
			AGridCell* GridCell = GetWorld()->SpawnActor<AGridCell>(BP_GridCell, PlacementPos, FRotator(0,0,0));
			GridCell->SetActorLocation(FVector(PlacementPos.X, PlacementPos.Y, 0));
			GridCell->SetCoord(h, w);
			GridCells.Add(GridCell);
		}
	}

	SetNeighbors();
}

void UGridSystem::SetNeighbors()
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

void UGridSystem::PlaceAnActor(AGridActor* Actor, FVector2D Coord)
{
	AGridCell* GridCell = FindGridByCoord(Coord);

	Actor->SetGridCellUnderActor(GridCell);
	Actor->SetActorLocation(GridCell->GetActorLocation());

	GridCell->SetPlacedActor(Actor);
	GridCell->SetIsAvailable(false);
}

void UGridSystem::MoveAnActor(AGridActor* Actor, AGridCell* TargetCell)
{
	UAStarAlgorithm* AStarAlgorithm = GetWorld()->GetGameInstance()->GetSubsystem<class UAStarAlgorithm>();

	TArray<AGridCell*> Path = AStarAlgorithm->AStarSearch(this,Actor->GridCellUnderActor,TargetCell);

	UGridMovement* MovementComponent = Actor->FindComponentByClass<UGridMovement>();

	MovementComponent->AddTargets(Path);

	Actor->GridCellUnderActor->SetIsAvailable(true);
	
	Actor->GridCellUnderActor = TargetCell;
	
	TargetCell->SetIsAvailable(false);
}


AGridCell* UGridSystem::FindGridByCoord(const FVector2D Coord)
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
