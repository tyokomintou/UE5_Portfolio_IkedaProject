// Copyright Epic Games, Inc. All Rights Reserved.


#include "UE5_Ikeda_PortfolioPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "UE5_Ikeda_PortfolioCameraManager.h"
#include "Blueprint/UserWidget.h"
#include "UE5_Ikeda_Portfolio.h"
#include "Widgets/Input/SVirtualJoystick.h"

AUE5_Ikeda_PortfolioPlayerController::AUE5_Ikeda_PortfolioPlayerController()
{
	// set the player camera manager class
	PlayerCameraManagerClass = AUE5_Ikeda_PortfolioCameraManager::StaticClass();
}

void AUE5_Ikeda_PortfolioPlayerController::BeginPlay()
{
	Super::BeginPlay();

	
	// only spawn touch controls on local player controllers
	if (ShouldUseTouchControls() && IsLocalPlayerController())
	{
		// spawn the mobile controls widget
		MobileControlsWidget = CreateWidget<UUserWidget>(this, MobileControlsWidgetClass);

		if (MobileControlsWidget)
		{
			// add the controls to the player screen
			MobileControlsWidget->AddToPlayerScreen(0);

		} else {

			UE_LOG(LogUE5_Ikeda_Portfolio, Error, TEXT("Could not spawn mobile controls widget."));

		}

	}
}

void AUE5_Ikeda_PortfolioPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// only add IMCs for local player controllers
	if (IsLocalPlayerController())
	{
		// Add Input Mapping Context
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);
			}

			// only add these IMCs if we're not using mobile touch input
			if (!ShouldUseTouchControls())
			{
				for (UInputMappingContext* CurrentContext : MobileExcludedMappingContexts)
				{
					Subsystem->AddMappingContext(CurrentContext, 0);
				}
			}
		}
	}
	
}

bool AUE5_Ikeda_PortfolioPlayerController::ShouldUseTouchControls() const
{
	// are we on a mobile platform? Should we force touch?
	return SVirtualJoystick::ShouldDisplayTouchInterface() || bForceTouchControls;
}
