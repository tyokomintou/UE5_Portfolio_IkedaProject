// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorActor.h"

ADoorActor::ADoorActor() {
	PrimaryActorTick.bCanEverTick = true;
}

void ADoorActor::BeginPlay( ) {
	Super::BeginPlay();
	InitialLocation = GetActorLocation();
	TargetLocation = InitialLocation;
}

void ADoorActor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	FVector CurrentLocation = GetActorLocation();

	if (!CurrentLocation.Equals(TargetLocation, 0.1f)) {
		FVector NewLocation = FMath::VInterpTo(CurrentLocation, TargetLocation, DeltaTime, MoveSpeed);
		SetActorLocation(NewLocation);
	}
}

void ADoorActor::OnTriggerSuccess( ) {
	Super::OnTriggerSuccess( );

	if (!isOpened) {
		OpenDoor();
		StartCameraEvent();
	}
	
}

void ADoorActor::OnTriggerFail() {
	Super::OnTriggerFail();

	if (isOpened)
	{
		CloseDoor();
	}
}

void ADoorActor:: OpenDoor() {
	isOpened = true;
	TargetLocation = InitialLocation + Move;

}

void ADoorActor::CloseDoor() {
	isOpened = false;
	TargetLocation = InitialLocation;
}