// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorActor.h"

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
	FVector NewLocation = GetActorLocation() + FVector(Move);
	SetActorRelativeLocation(NewLocation);

}

void ADoorActor::CloseDoor() {
	isOpened = false;
	FVector NewLocation = GetActorLocation() - FVector(Move);
	SetActorRelativeLocation(NewLocation);
}