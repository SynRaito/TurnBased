// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
struct TURNBASED_API AStarCellProperties
{
	int ParentRow,ParentColumn;
	double F,G,H;
};
