// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TurnBased/Systems/Grid/GridCell.h"
#include "TurnBased/Systems/Grid/GridSystem.h"
#include "AStarAlgorithm.generated.h"
/**
 * 
 */

UCLASS()
class TURNBASED_API UAStarAlgorithm : public UObject
{
	GENERATED_BODY()

public:
	TArray<AGridCell*> AStarSearch(AGridSystem* GridSystem, AGridCell* Source, AGridCell* Destination);
	

private:
	double CalculateHValue(int Row, int Col, FVector2D Dest);
	TArray<AGridCell*> TracePath(AGridSystem* GridSystem, AGridCell* Dest);
	
};
