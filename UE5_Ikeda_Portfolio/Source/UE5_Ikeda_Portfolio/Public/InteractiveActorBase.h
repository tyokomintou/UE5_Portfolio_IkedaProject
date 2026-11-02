// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Switch.h"
#include "Camera/CameraActor.h"
#include "InteractiveActorBase.generated.h"

UCLASS()
class UE5_IKEDA_PORTFOLIO_API AInteractiveActorBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractiveActorBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//このアクターがレベル上のどのSwitchで起動するかの配列
	UPROPERTY( EditInstanceOnly, Category = "Puzzle" )
	TArray<ASwitch*> RequiredSwitches; 

	UPROPERTY(EditInstanceOnly, Category = "Puzzle")
	bool checkConditions;

	UFUNCTION( )
	void HandleSwitchStateChanged( ASwitch* ChangedSwitch, bool bNewState );

	//起動するSwitchと起動する順番をチェックする
	virtual bool CheckConditions( );

	virtual void OnTriggerSuccess( );
	virtual void OnTriggerFail();

	//インタラクト後のカメライベント

	UPROPERTY(EditInstanceOnly,  Category = "CameraEvent")
	ACameraActor* TargetCameraActor;

	UPROPERTY(EditAnywhere, Category = "CameraEvent")
	float CameraFadeInTime = 0.5f;

	UPROPERTY(EditAnywhere, Category = "CameraEvent")
	float CameraFadeOutTime = 0.5f;

	UPROPERTY(EditAnywhere, Category = "CameraEvent")
	float CameraEventTime = 2.0f;

	UPROPERTY(VisibleAnywhere, Category = "CameraEvent")
	FTimerHandle CameraEventTimerHandle;

	UPROPERTY(EditAnywhere, Category = "CameraEvent")
	bool bDisableInputDuring = true;

	void StartCameraEvent();
	void SwitchToTargetCamera();
	void EndCameraEvent();
	void SwitchToPlayerCamera();



private:
	UPROPERTY()
	TArray<ASwitch*> CurrentActivatedOrder;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
