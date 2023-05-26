// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Chaos/Pair.h"
#include "TimeWrapper.generated.h"

/**
 * 
 */
UCLASS()
class TURNBASED_API UTimeWrapper : public UObject
{
	GENERATED_BODY()
public:
	UTimeWrapper();
	
public:
	TArray<int> ExecutionOrder;
	TArray<Chaos::Pair<int,TFunction<void()>>> FunctionList;
	TArray<Chaos::Pair<int,float>> WaitList;

public:
	void WaitForSeconds(float);
	void RunFunction(TFunction<void()>);
	int FindWait(int Id);
	int FindFunc(int Id);
};