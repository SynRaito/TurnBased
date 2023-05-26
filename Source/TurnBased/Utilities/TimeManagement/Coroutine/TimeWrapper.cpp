// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeWrapper.h"

UTimeWrapper::UTimeWrapper()
{
}

void UTimeWrapper::WaitForSeconds(float Time)
{
	int Order = ExecutionOrder.Num();
	Chaos::Pair<int,float> Pair;
	Pair.First = Order;
	Pair.Second = Time;
	WaitList.Add(Pair);
	ExecutionOrder.Add(Order);
}

void UTimeWrapper::RunFunction(TFunction<void()> Func)
{
	int Order = ExecutionOrder.Num();
	Chaos::Pair<int,TFunction<void()>> Pair;
	Pair.First = Order;
	Pair.Second = Func;
	FunctionList.Add(Pair);
	ExecutionOrder.Add(Order);
}

int UTimeWrapper::FindWait(int Id)
{
	int Counter = 0;
	for (auto Element : WaitList)
	{
		if(Element.First == Id)
		{
			return Counter;
		}
		Counter++;
	}

	return -1;
}

int UTimeWrapper::FindFunc(int Id)
{
	int Counter = 0;
	for (auto Element : FunctionList)
	{
		if(Element.First == Id)
		{
			return Counter;
		}
		Counter++;
	}

	return -1;
}
