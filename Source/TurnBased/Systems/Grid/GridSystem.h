// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GridCell.h"
#include "GameFramework/Actor.h"
#include "GridSystem.generated.h"

class AStarAlgorithm;

UCLASS()
class TURNBASED_API AGridSystem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGridSystem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	AStarAlgorithm* AStar;

	UPROPERTY(VisibleAnywhere)
	TArray<AGridCell*> GridCells;
	int SystemColumn,SystemRow;
	FVector2D SystemStartPosition;

	UPROPERTY(EditAnywhere);
	TSubclassOf<AGridCell> BP_GridCell;
	UPROPERTY(EditAnywhere)
	AGridActor* TestPlacementActor;
	
	void CreateGrids(FVector2D StartPos, int Row, int Column);
	
	void SetNeighbors();

	void PlaceAnActor(AGridActor* Actor, FVector2D Coord);

	AGridCell* FindGridByCoord(const FVector2D Coord);
};