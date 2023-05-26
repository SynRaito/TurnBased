// Fill out your copyright notice in the Description page of Project Settings.


#include "CoroutineManager.h"

void UCoroutineManager::StartCoroutine(UTimeWrapper* TimeWrapper)
{
	float Timer = 0;
	if (TimeWrapper != nullptr)
	{
		for (auto Order : TimeWrapper->ExecutionOrder)
		{
			int TimeIndex = TimeWrapper->FindWait(Order);
			int FuncIndex = TimeWrapper->FindFunc(Order);
			if (TimeIndex != -1)
			{
				Timer += TimeWrapper->WaitList[TimeIndex].Second;
			}
			else if (FuncIndex != -1)
			{
				if (Timer == 0)
				{
					TimeWrapper->FunctionList[FuncIndex].Second();
				}
				else
				{
					FTimerDelegate Delegate;
					FTimerHandle TimerHandle;
					
					Delegate.BindLambda(TimeWrapper->FunctionList[FuncIndex].Second);
					GetWorld()->GetTimerManager().SetTimer(TimerHandle, Delegate, 1, false, Timer);
				}
			}
		}
	}
}
