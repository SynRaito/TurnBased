﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "GridActor.h"


// Sets default values
AGridActor::AGridActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGridActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGridActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

const AGridCell* AGridActor::GetGridCellUnderActor()
{
	return GridCellUnderActor;
}

void AGridActor::SetGridCellUnderActor(AGridCell* GridCell)
{
	GridCellUnderActor = GridCell;
}