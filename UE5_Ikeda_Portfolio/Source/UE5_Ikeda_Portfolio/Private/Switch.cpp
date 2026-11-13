#include "Switch.h"
#include "Materials/MaterialInterface.h"

ASwitch::ASwitch( ) {
	PrimaryActorTick.bCanEverTick = true;
}

void ASwitch::BeginPlay( ) {
	Super::BeginPlay( );

	TArray<UStaticMeshComponent*> MeshComponents;
	GetComponents<UStaticMeshComponent>( MeshComponents );

	for ( UStaticMeshComponent* Mesh : MeshComponents ) {
		if ( !Mesh ) continue;

		UMaterialInterface* Mat = Mesh->GetMaterial( 0 );
		if ( Mat && Mat->GetName( ).Contains( TEXT( "SwitchButtom" ) ) ) {
			SwitchMesh = Mesh;
			DynamicMaterial = SwitchMesh->CreateAndSetMaterialInstanceDynamic( 0 );
			break;
		}
	}
	UpdateSwitchColor( );
}

void ASwitch::Tick( float DeltaTime ) {
	Super::Tick( DeltaTime );
}

void ASwitch::Interact_Implementation( AActor* Interactor ) {
	bIsOn = !bIsOn;
	OnSwitchStateChanged.Broadcast( this, bIsOn );
	UpdateSwitchColor( );
}

void ASwitch::UpdateSwitchColor( ) {
	if ( DynamicMaterial ) {
		FLinearColor TargetColor = bIsOn ? OnColor : OffColor;
		DynamicMaterial->SetVectorParameterValue( ColorParamName, TargetColor );
	}
}