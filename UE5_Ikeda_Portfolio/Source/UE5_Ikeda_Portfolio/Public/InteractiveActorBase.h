// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Switch.h"
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
	UPROPERTY( EditInstanceOnly, BlueprintReadOnly, Category = "Puzzle" )
	TArray<ASwitch*> RequiredSwitches; 

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Puzzle")
	bool checkConditions;

	void HandleSwitchStateChanged( ASwitch* ChangedSwitch, bool bNewState );

	//起動するSwitchと起動する順番をチェックする
	virtual bool CheckConditions( );

	void OnTriggerSuccess( );

	virtual void OnTriggerSuccess_Implementation( );


private:
	UPROPERTY()
	TArray<ASwitch*> CurrentActivatedOrder;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
