// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class TURNBASED_API GameplayMath
{
public:
	static FVector ClampPosition(const FVector Position, const FVector PosOne, const FVector PosTwo);
};
