// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TimeWrapper.h"
#include "CoreMinimal.h"
#include "CoroutineManager.generated.h"

/**
 * 
 */
UCLASS()
class TURNBASED_API UCoroutineManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	
	void StartCoroutine(UTimeWrapper* TimeWrapper);
};

