// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "InteractableInterface.h"
#include "Switch.generated.h"

class ASwitch;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSwitchStateChanged, ASwitch*, SwitchActor, bool, bNewState);

UCLASS( )
class UE5_IKEDA_PORTFOLIO_API ASwitch : public AActor, public IInteractableInterface {
	GENERATED_BODY( )

public:
	ASwitch( );
	virtual void Tick( float DeltaTime ) override;

	bool IsOn() const { return bIsOn; }

	virtual void Interact_Implementation( AActor* Interactor ) override;

	UPROPERTY( BlueprintAssignable, Category = "Events" )
	FOnSwitchStateChanged OnSwitchStateChanged;

protected:
	virtual void BeginPlay( ) override;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Switch" )
	bool bIsOn = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Switch|Components" )
	UStaticMeshComponent* SwitchMesh;

	UPROPERTY( EditAnywhere, Category = "Switch|Color")
	FLinearColor OffColor = FLinearColor::Red;

	UPROPERTY(EditAnywhere, Category = "Switch|Color")
	FLinearColor OnColor = FLinearColor::Green;

	UPROPERTY(EditAnywhere, Category = "Switch|Color")
	FName ColorParamName = FName("BaseColor");

private:
	UPROPERTY()
	UMaterialInstanceDynamic* DynamicMaterial;

	void UpdateSwitchColor();
};