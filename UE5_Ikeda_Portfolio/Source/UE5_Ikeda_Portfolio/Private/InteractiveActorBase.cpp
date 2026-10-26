// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveActorBase.h"

// Sets default values
AInteractiveActorBase::AInteractiveActorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInteractiveActorBase::BeginPlay()
{
	Super::BeginPlay();

	for ( ASwitch* Switch : RequiredSwitches ) {
		if ( Switch ) {
			Switch->OnSwitchStateChanged.AddDynamic( this, &AInteractiveActorBase::HandleSwitchStateChanged );
		}
	}
	
}

// Called every frame
void AInteractiveActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractiveActorBase::HandleSwitchStateChanged( ASwitch* ChangedSwitch, bool bNewState ) {
	if ( bNewState ) {
		CurrentActivatedOrder.AddUnique( ChangedSwitch );
	} else {
		CurrentActivatedOrder.Remove( ChangedSwitch );
	}

	if ( CheckConditions( ) ) {
		OnTriggerSuccess( );
	}
}

bool AInteractiveActorBase::CheckConditions( ) {
	if (checkConditions) {
		if (CurrentActivatedOrder.Num() != RequiredSwitches.Num()) {
			return false;
		}

		for (int32 i = 0; i < RequiredSwitches.Num(); ++i) {
			if (CurrentActivatedOrder[i] != RequiredSwitches[i]) {
				return false;
			}
		}

		return true;
	}
	else {
		for (ASwitch* SwitchActor : RequiredSwitches)
		{
			if (SwitchActor && !SwitchActor->IsOn())
			{
				return false;
			}
		}
	}
	return true;
}

void AInteractiveActorBase::OnTriggerSuccess_Implementation( ) {
	UE_LOG( LogTemp, Log, TEXT( "Puzzle Cleared!" ) );
}