#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractableInterface.generated.h"

UINTERFACE( MinimalAPI, Blueprintable )
class UInteractableInterface : public UInterface {
	GENERATED_BODY( )
};

class UE5_IKEDA_PORTFOLIO_API IInteractableInterface {
	GENERATED_BODY( )

public:
	void Interact( AActor* Interactor );
};