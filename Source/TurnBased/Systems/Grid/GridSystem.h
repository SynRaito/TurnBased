// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GridCell.h"
#include "GameFramework/Actor.h"
#include "GridSystem.generated.h"

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
	TArray<AGridCell*> GridCells;
	int SystemWidth,SystemHeight;
	FVector2D SystemStartPosition;

	UPROPERTY(EditAnywhere);
	TSubclassOf<AGridCell> BP_GridCell;
	
	void CreateGrids(FVector2D StartPos, int Height, int Width);
	
	void SetNeighbors();

	AGridCell* FindGridByCoord(const FVector2D Coord);
};