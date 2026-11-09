// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveActorBase.h"
#include "DoorActor.generated.h"

/**
 * 
 */
UCLASS()
class UE5_IKEDA_PORTFOLIO_API ADoorActor : public AInteractiveActorBase
{
	GENERATED_BODY()

public:
	ADoorActor();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditInstanceOnly, Category = "Door")
	FVector Move = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(EditInstanceOnly, Category = "Door")
	float MoveSpeed = 0.0f;

private:
	UPROPERTY()
	bool isOpened = false;

	FVector InitialLocation;
	FVector TargetLocation;

protected:
	virtual void BeginPlay() override;

	virtual void OnTriggerSuccess() override;
	virtual void OnTriggerFail() override;

	void OpenDoor( );
	void CloseDoor( );

};
