// Fill out your copyright notice in the Description page of Project Settings.

#include "Switch.h"

ASwitch::ASwitch( ) {
	PrimaryActorTick.bCanEverTick = true;
}

void ASwitch::BeginPlay( ) {
	Super::BeginPlay( );

	if (SwitchMesh && SwitchMesh->GetMaterial(0)) {
		DynamicMaterial = SwitchMesh->CreateAndSetMaterialInstanceDynamic(0);
	}
	else
	{
		UStaticMeshComponent* FoundMesh = FindComponentByClass<UStaticMeshComponent>();
		if (FoundMesh && FoundMesh->GetMaterial(0)) {
			SwitchMesh = FoundMesh;
			DynamicMaterial = SwitchMesh->CreateAndSetMaterialInstanceDynamic(0);
		}
	}
	UpdateSwitchColor();
}

void ASwitch::Tick( float DeltaTime ) {
	Super::Tick( DeltaTime );
}

void ASwitch::Interact_Implementation( AActor* Interactor ) {
	bIsOn = !bIsOn;
	OnSwitchStateChanged.Broadcast( this, bIsOn );
	UpdateSwitchColor();
}

void ASwitch::UpdateSwitchColor() {
	if (DynamicMaterial) {
		FLinearColor TargetColor = bIsOn ? OnColor : OffColor;
		DynamicMaterial->SetVectorParameterValue(ColorParamName, TargetColor);
	}
}