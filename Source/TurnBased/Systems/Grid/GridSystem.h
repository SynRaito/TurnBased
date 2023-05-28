// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TurnBased/Utilities/TimeManagement/Coroutine/TimeWrapper.h"
#include "CoreMinimal.h"
#include "GridCell.h"
#include "GameFramework/Actor.h"
#include "GridSystem.generated.h"

UCLASS()
class TURNBASED_API UGridSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(VisibleAnywhere)
	TArray<AGridCell*> GridCells;
	int SystemColumn,SystemRow;
	FVector2D SystemStartPosition;
	
	void CreateGrids(TSubclassOf<AGridCell> BP_GridCell ,FVector2D StartPos, int Row, int Column);
	
	void SetNeighbors();

	void PlaceAnActor(AGridActor* Actor, FVector2D Coord);

	UFUNCTION(BlueprintCallable)
	void MoveAnActor(AGridActor* Actor , AGridCell* TargetCell);

	AGridCell* FindGridByCoord(const FVector2D Coord);
};