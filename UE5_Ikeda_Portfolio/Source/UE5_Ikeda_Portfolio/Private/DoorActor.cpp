// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorActor.h"

void ADoorActor::OnTriggerSuccess_Implementation( ) {
	Super::OnTriggerSuccess_Implementation( );

	if (!isOpened) {
		OpenDoor();
	}
	
}

void ADoorActor::OnTriggerFail_Implementation() {
	Super::OnTriggerFail_Implementation();

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