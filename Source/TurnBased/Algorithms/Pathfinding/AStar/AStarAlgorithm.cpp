// Fill out your copyright notice in the Description page of Project Settings.


#include "AStarAlgorithm.h"


TArray<AGridCell*> UAStarAlgorithm::AStarSearch(UGridSystem* GridSystem, AGridCell* Source, AGridCell* Destination)
{
	int i, j;

	for (i = 0; i < GridSystem->SystemRow; i++)
	{
		for (j = 0; j < GridSystem->SystemColumn; j++)
		{
			AGridCell* Cell = GridSystem->FindGridByCoord(FVector2D(i, j));
			Cell->AStarProperties.F = FLT_MAX;
			Cell->AStarProperties.G = FLT_MAX;
			Cell->AStarProperties.H = FLT_MAX;
			Cell->AStarProperties.ParentRow = -1;
			Cell->AStarProperties.ParentColumn = -1;
		}
	}

	i = Source->GetCoord().X, j = Source->GetCoord().Y;
	AGridCell* Cell = GridSystem->FindGridByCoord(FVector2D(i, j));
	Cell->AStarProperties.F = 0.0;
	Cell->AStarProperties.G = 0.0;
	Cell->AStarProperties.H = 0.0;
	Cell->AStarProperties.ParentRow = -1;
	Cell->AStarProperties.ParentColumn = -1;

	TArray<AGridCell*> OpenList, ClosedList;

	OpenList.Add(Cell);

	bool FoundDest = false;

	while (!OpenList.IsEmpty())
	{
		AGridCell* CurrentCell = OpenList[0];

		OpenList.Remove(CurrentCell);

		i = CurrentCell->GetCoord().X;
		j = CurrentCell->GetCoord().Y;
		ClosedList.Add(CurrentCell);

		double GNew, HNew, FNew;

		//----------- 1st Successor (North) ------------

		AGridCell* NorthCell = CurrentCell->GetNeighbor(EGridNeighborDirections::North);
		if (NorthCell != nullptr)
		{
			if (NorthCell->GetCoord() == Destination->GetCoord())
			{
				NorthCell->AStarProperties.ParentRow = i;
				NorthCell->AStarProperties.ParentColumn = j;
				printf("The destination cell is found\n");
				return TracePath(GridSystem, Destination);
			}
			else if (!ClosedList.Contains(NorthCell)
				&& NorthCell->GetIsAvailable())
			{
				GNew = CurrentCell->AStarProperties.G + 1.0;
				HNew = CalculateHValue(NorthCell->GetCoord().X, NorthCell->GetCoord().Y, Destination->GetCoord());
				FNew = GNew + HNew;

				if (NorthCell->AStarProperties.F == FLT_MAX
					|| NorthCell->AStarProperties.F > FNew)
				{
					OpenList.Add(NorthCell);

					NorthCell->AStarProperties.F = FNew;
					NorthCell->AStarProperties.G = GNew;
					NorthCell->AStarProperties.H = HNew;
					NorthCell->AStarProperties.ParentRow = i;
					NorthCell->AStarProperties.ParentColumn = j;
				}
			}
		}

		//----------- 2nd Successor (South) ------------

		AGridCell* SouthCell = CurrentCell->GetNeighbor(EGridNeighborDirections::South);
		if (SouthCell != nullptr)
		{
			if (SouthCell->GetCoord() == Destination->GetCoord())
			{
				SouthCell->AStarProperties.ParentRow = i;
				SouthCell->AStarProperties.ParentColumn = j;
				printf("The destination cell is found\n");
				return TracePath(GridSystem, Destination);
			}
			else if (!ClosedList.Contains(SouthCell)
				&& SouthCell->GetIsAvailable())
			{
				GNew = CurrentCell->AStarProperties.G + 1.0;
				HNew = CalculateHValue(SouthCell->GetCoord().X, SouthCell->GetCoord().Y, Destination->GetCoord());
				FNew = GNew + HNew;

				if (SouthCell->AStarProperties.F == FLT_MAX
					|| SouthCell->AStarProperties.F > FNew)
				{
					OpenList.Add(SouthCell);

					SouthCell->AStarProperties.F = FNew;
					SouthCell->AStarProperties.G = GNew;
					SouthCell->AStarProperties.H = HNew;
					SouthCell->AStarProperties.ParentRow = i;
					SouthCell->AStarProperties.ParentColumn = j;
				}
			}
		}

		//----------- 3rd Successor (East) ------------

		AGridCell* EastCell = CurrentCell->GetNeighbor(EGridNeighborDirections::East);
		if (EastCell != nullptr)
		{
			if (EastCell->GetCoord() == Destination->GetCoord())
			{
				EastCell->AStarProperties.ParentRow = i;
				EastCell->AStarProperties.ParentColumn = j;
				printf("The destination cell is found\n");
				return TracePath(GridSystem, Destination);
			}
			else if (!ClosedList.Contains(EastCell)
				&& EastCell->GetIsAvailable())
			{
				GNew = CurrentCell->AStarProperties.G + 1.0;
				HNew = CalculateHValue(EastCell->GetCoord().X, EastCell->GetCoord().Y, Destination->GetCoord());
				FNew = GNew + HNew;

				if (EastCell->AStarProperties.F == FLT_MAX
					|| EastCell->AStarProperties.F > FNew)
				{
					OpenList.Add(EastCell);
					
					EastCell->AStarProperties.F = FNew;
					EastCell->AStarProperties.G = GNew;
					EastCell->AStarProperties.H = HNew;
					EastCell->AStarProperties.ParentRow = i;
					EastCell->AStarProperties.ParentColumn = j;
				}
			}
		}

		//----------- 4th Successor (West) ------------

		AGridCell* WestCell = CurrentCell->GetNeighbor(EGridNeighborDirections::West);
		if (WestCell != nullptr)
		{
			if (WestCell->GetCoord() == Destination->GetCoord())
			{
				WestCell->AStarProperties.ParentRow = i;
				WestCell->AStarProperties.ParentColumn = j;
				printf("The destination cell is found\n");

				return TracePath(GridSystem, Destination);
			}
			else if (!ClosedList.Contains(WestCell)
				&& WestCell->GetIsAvailable())
			{
				GNew = CurrentCell->AStarProperties.G + 1.0;
				HNew = CalculateHValue(WestCell->GetCoord().X, WestCell->GetCoord().Y, Destination->GetCoord());
				FNew = GNew + HNew;

				if (WestCell->AStarProperties.F == FLT_MAX
					|| WestCell->AStarProperties.F > FNew)
				{
					OpenList.Add(WestCell);

					// Update the details of this cell
					WestCell->AStarProperties.F = FNew;
					WestCell->AStarProperties.G = GNew;
					WestCell->AStarProperties.H = HNew;
					WestCell->AStarProperties.ParentRow = i;
					WestCell->AStarProperties.ParentColumn = j;
				}
			}
		}
	}

	// No Path

	return TracePath(GridSystem, Destination);
}

double UAStarAlgorithm::CalculateHValue(int Row, int Col, FVector2D Dest)
{
	return ((double)sqrt(
		(Row - Dest.X) * (Row - Dest.X)
		+ (Col - Dest.Y) * (Col - Dest.Y)));
}

TArray<AGridCell*> UAStarAlgorithm::TracePath(UGridSystem* GridSystem, AGridCell* Dest)
{
	TArray<AGridCell*> Path;
	AGridCell* CurrentCell = Dest;
	while (CurrentCell != nullptr)
	{
		Path.Add(CurrentCell);
		CurrentCell = GridSystem->FindGridByCoord(FVector2D(CurrentCell->AStarProperties.ParentRow,
		                                                    CurrentCell->AStarProperties.ParentColumn));
	}
	Path.RemoveAt(Path.Num()-1,1);
	Algo::Reverse(Path);
	
	return Path;
}
