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

protected:
	virtual void OnTriggerSuccessImplementation( ) override;

	UFUNCTION(BlueprintImplementableEvent, category = "Door" )
	void OpenDoor( );
	
};
