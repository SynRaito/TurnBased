// Fill out your copyright notice in the Description page of Project Settings.


#include "GridMovement.h"


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

	HandleMovement();
}


// Called every frame
void UGridMovement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

void UGridMovement::AddTarget(AGridCell* TargetGridCell)
{
	TargetQueue.Enqueue(TargetGridCell->GetActorLocation());
	CheckTarget();
}

void UGridMovement::AddTargets(TArray<AGridCell*> TargetGridCells)
{
	for (AGridCell* Cell : TargetGridCells)
	{
		TargetQueue.Enqueue(Cell->GetActorLocation());
	}
	CheckTarget();
}

void UGridMovement::CheckTarget()
{
	if(TargetPosition != GetOwner()->GetActorLocation() && isMoving == false)
	{
		StartPosition = GetOwner()->GetActorLocation();
		TargetQueue.Dequeue(TargetPosition);
		isMoving = true;
	}
}

void UGridMovement::HandleMovement()
{
	if(isMoving)
	{
		if(HasArrived())
		{
			if(TargetQueue.IsEmpty())
			{
				isMoving = false;
			}
			else
			{
				StartPosition = GetOwner()->GetActorLocation();
				TargetQueue.Dequeue(TargetPosition);
			}
		}
		else
		{
			FVector CurrentLocation = GetOwner()->GetActorLocation();
			GetOwner()->SetActorLocation(ClampVector(CurrentLocation + (TargetPosition - StartPosition) * DeltaTime , StartPosition , TargetPosition));
			//isMoving = false;
		}
	}
}


bool UGridMovement::HasArrived()
{
	return TargetPosition == GetOwner()->GetActorLocation();
}

