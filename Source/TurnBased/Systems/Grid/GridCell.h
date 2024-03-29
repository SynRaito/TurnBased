// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GridActor.h"
#include "GameFramework/Actor.h"
#include "Enums/GridNeighborDirections.h"
#include "TurnBased/Algorithms/Pathfinding/AStar/AStarCellProperties.h"
#include "GridCell.generated.h"

UCLASS()
class TURNBASED_API AGridCell : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGridCell();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
private:
	bool bIsAvailable = true;
	UPROPERTY(VisibleAnywhere)
	FVector2D Coord;
	UPROPERTY(VisibleAnywhere)
	AGridActor* PlacedActor = nullptr;

	//Neighbors
	UPROPERTY(VisibleAnywhere)
	AGridCell* North = nullptr;
	UPROPERTY(VisibleAnywhere)
	AGridCell* East = nullptr;
	UPROPERTY(VisibleAnywhere)
	AGridCell* South = nullptr;
	UPROPERTY(VisibleAnywhere)
	AGridCell* West = nullptr;

public:
	AStarCellProperties AStarProperties;
	
public:
	bool GetIsAvailable();
	void SetIsAvailable(bool State);
	
	FVector2D GetCoord();
	void SetCoord(FVector2D C);
	void SetCoord(int X, int Y);
	
	AActor* GetPlacedActor();
	void SetPlacedActor(AGridActor* Actor);
	
	AGridCell* GetNeighbor (EGridNeighborDirections Direction);
	void SetNeighbor (EGridNeighborDirections Direction, AGridCell* GridCell);

	void SetFree();
};
