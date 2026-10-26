// Fill out your copyright notice in the Description page of Project Settings.

#include "Switch.h"

ASwitch::ASwitch( ) {
	PrimaryActorTick.bCanEverTick = true;
}

void ASwitch::BeginPlay( ) {
	Super::BeginPlay( );
}

void ASwitch::Tick( float DeltaTime ) {
	Super::Tick( DeltaTime );
}

void ASwitch::Interact_Implementation( AActor* Interactor ) {
	bIsOn = !bIsOn;
	OnSwitchStateChanged.Broadcast( this, bIsOn );
}