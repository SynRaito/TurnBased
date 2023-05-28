// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayMath.h"

FVector GameplayMath::ClampPosition(const FVector Position, const FVector PosOne, const FVector PosTwo)
{
	FVector Min, Max;
	if (PosOne.X > PosTwo.X)
	{
		Min.X = PosTwo.X;
		Max.X = PosOne.X;
	}
	else
	{
		Min.X = PosOne.X;
		Max.X = PosTwo.X;
	}
	if (PosOne.Y > PosTwo.Y)
	{
		Min.Y = PosTwo.Y;
		Max.Y = PosOne.Y;
	}
	else
	{
		Min.Y = PosOne.Y;
		Max.Y = PosTwo.Y;
	}
	if (PosOne.Z > PosTwo.Z)
	{
		Min.Z = PosTwo.Z;
		Max.Z = PosOne.Z;
	}
	else
	{
		Min.Z = PosOne.Z;
		Max.Z = PosTwo.Z;
	}

	return ClampVector(Position, Min, Max);
}
