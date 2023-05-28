// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TurnBased/Systems/Grid/GridActor.h"
#include "TurnBasePlayer.generated.h"

UCLASS()
class TURNBASED_API ATurnBasePlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATurnBasePlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(VisibleAnywhere)
	AGridActor* SelectedActor;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AGridActor> TestPlacementActor;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AGridCell> GridCell;
public:
	UFUNCTION(BlueprintCallable)
	void TestRandomMove();
};
