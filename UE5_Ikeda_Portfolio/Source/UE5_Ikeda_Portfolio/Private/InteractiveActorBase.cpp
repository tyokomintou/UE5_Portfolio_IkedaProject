// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveActorBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"

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
	else {
		OnTriggerFail();
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

void AInteractiveActorBase::OnTriggerSuccess( ) {
	UE_LOG( LogTemp, Log, TEXT( "Puzzle Cleared!" ) );
}

void AInteractiveActorBase::OnTriggerFail() {
	UE_LOG(LogTemp, Log, TEXT("Puzzle Cleared!"));
}


void AInteractiveActorBase::StartCameraEvent() {
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if (!PC || !TargetCameraActor) return;

	if (bDisableInputDuring && PC->GetPawn())
	{
		PC->GetPawn()->DisableInput(PC);
	}

	// 画面を黒へフェードアウト (Alpha 0.0 -> 1.0)
	if (PC->PlayerCameraManager)
	{
		PC->PlayerCameraManager->StartCameraFade(0.0f, 1.0f, CameraFadeInTime, FLinearColor::Black, false, true);
	}

	// フェードアウト完了後に視点を切り替えるタイマー
	GetWorldTimerManager().SetTimer(
		CameraEventTimerHandle,
		this,
		&AInteractiveActorBase::SwitchToTargetCamera,
		CameraFadeInTime,
		false
	);

}

void AInteractiveActorBase::SwitchToTargetCamera(){ 
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if (!PC || !TargetCameraActor) return;

	PC->SetViewTarget(TargetCameraActor);

	// 画面を黒へフェードアウト (Alpha 1.0 -> 0.0)
	if (PC->PlayerCameraManager)
	{
		PC->PlayerCameraManager->StartCameraFade(1.0f, 0.0f, CameraFadeInTime, FLinearColor::Black, false, true);
	}

	// フェードアウト完了後に視点を切り替えるタイマー
	GetWorldTimerManager().SetTimer(
		CameraEventTimerHandle,
		this,
		&AInteractiveActorBase::EndCameraEvent,
		CameraFadeInTime,
		false
	);

}

void AInteractiveActorBase::EndCameraEvent() {
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if (!PC) return;



	// 画面を黒へフェードアウト (Alpha 0.0 -> 1.0)
	if (PC->PlayerCameraManager)
	{
		PC->PlayerCameraManager->StartCameraFade(0.0f, 1.0f, CameraFadeInTime, FLinearColor::Black, false, true);
	}

	// フェードアウト完了後に視点を切り替えるタイマー
	GetWorldTimerManager().SetTimer(
		CameraEventTimerHandle,
		this,
		&AInteractiveActorBase::SwitchToPlayerCamera,
		CameraFadeInTime,
		false
	);

}

void AInteractiveActorBase::SwitchToPlayerCamera() {
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if (!PC) return;

	APawn* PlayerPawn = PC->GetPawn();
	if (PlayerPawn)
	{
		PC->SetViewTarget(PlayerPawn);

		if (bDisableInputDuring)
		{
			PlayerPawn->EnableInput(PC);
		}
	}

	if (PC->PlayerCameraManager)
	{
		PC->PlayerCameraManager->StartCameraFade(1.0f, 0.0f, CameraFadeInTime, FLinearColor::Black, false, true);
	}


}