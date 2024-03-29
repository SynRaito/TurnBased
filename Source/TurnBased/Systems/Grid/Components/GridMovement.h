﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../GridCell.h"
#include "TurnBased/Systems/Grid/GridSystem.h"
#include "GridMovement.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TURNBASED_API UGridMovement : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGridMovement();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(VisibleAnywhere)
	AGridCell* CurrentGrid;

private:
	bool isMoving = false;
	UPROPERTY(VisibleAnywhere)
	FVector TargetPosition = FVector(-1,-1,-1);
	UPROPERTY(VisibleAnywhere)
	FVector StartPosition;
	
	TQueue<FVector> TargetQueue;

private:
	UFUNCTION()
	void HandleMovement(float DeltaTime);
	
public:
	UFUNCTION()
	void AddTarget(AGridCell* TargetGridCell);
	UFUNCTION()
	void AddTargets(TArray<AGridCell*> TargetGridCells);
	
	UFUNCTION(BlueprintCallable)
	bool HasArrived();
};
