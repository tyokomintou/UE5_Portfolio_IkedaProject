// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"
#include "Switch.generated.h"

class ASwitch;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSwitchStateChanged, ASwitch*, SwitchActor, bool, bNewState);

UCLASS( )
class UE5_IKEDA_PORTFOLIO_API ASwitch : public AActor, public IInteractableInterface {
	GENERATED_BODY( )

public:
	ASwitch( );
	bool IsOn() const { return bIsOn; }

	virtual void Interact_Implementation( AActor* Interactor ) override;

	UPROPERTY( BlueprintAssignable, Category = "Events" )
	FOnSwitchStateChanged OnSwitchStateChanged;

protected:
	virtual void BeginPlay( ) override;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Switch" )
	bool bIsOn = false;

public:
	virtual void Tick( float DeltaTime ) override;
};