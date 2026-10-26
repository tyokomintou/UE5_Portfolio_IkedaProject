// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorActor.h"

void ADoorActor::OnTriggerSuccessImplementation( ) {
	Super::OnTriggerSuccessImplementation( );
	OpenDoor( );
}