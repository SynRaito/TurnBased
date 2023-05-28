// Fill out your copyright notice in the Description page of Project Settings.


#include "GridMovement.h"

#include "TurnBased/Library/GameplayMath.h"


// Sets default values for this component's properties
UGridMovement::UGridMovement()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGridMovement::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UGridMovement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	HandleMovement(DeltaTime);
}

void UGridMovement::AddTarget(AGridCell* TargetGridCell)
{
	TargetQueue.Enqueue(TargetGridCell->GetActorLocation());
}

void UGridMovement::AddTargets(TArray<AGridCell*> TargetGridCells)
{
	for (AGridCell* Cell : TargetGridCells)
	{
		TargetQueue.Enqueue(Cell->GetActorLocation());
	}
}

void UGridMovement::HandleMovement(float DeltaTime)
{
	if (isMoving)
	{
		if (HasArrived())
		{
			isMoving = false;
		}
		else
		{
			FVector CurrentLocation = GetOwner()->GetActorLocation();
			GetOwner()->SetActorLocation(GameplayMath::ClampPosition(CurrentLocation + (TargetPosition - StartPosition) * DeltaTime,
			                                         StartPosition, TargetPosition));
		}
	}
	else
	{
		if (!TargetQueue.IsEmpty())
		{
			isMoving = true;
			StartPosition = GetOwner()->GetActorLocation();
			TargetQueue.Dequeue(TargetPosition);
		}
	}
}

bool UGridMovement::HasArrived()
{
	return TargetPosition == GetOwner()->GetActorLocation();
}