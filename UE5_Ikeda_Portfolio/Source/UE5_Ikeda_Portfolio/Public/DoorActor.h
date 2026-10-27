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
	UPROPERTY(EditInstanceOnly, Category = "Door")
	FVector Move = FVector(0.0f, 0.0f, 0.0f);

protected:
	virtual void OnTriggerSuccess_Implementation( ) override;

	void OpenDoor( );

};
