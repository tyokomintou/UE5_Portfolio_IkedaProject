// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorActor.h"

void ADoorActor::OnTriggerSuccess_Implementation( ) {
	Super::OnTriggerSuccess_Implementation( );
	OpenDoor( );
	
}

void ADoorActor:: OpenDoor() {
	FVector NewLocation = GetActorLocation() + FVector(Move);
	SetActorRelativeLocation(NewLocation);
}