// Fill out your copyright notice in the Description page of Project Settings.

#include "KartRacer.h"
#include "KartController.h"
#include "../GamepadUMGPlugin/Public/VirtualCursorFunctionLibrary.h"
#include "Blueprint/UserWidget.h"


void AKartController::BeginPlay()
{
	UVirtualCursorFunctionLibrary::DisableVirtualCursor(this);
	FPlatformProcess::Sleep(2);
	AddHud();
}

void AKartController::AddHud()
{
	if (wRaceWidget) // Check if the Asset is assigned in the blueprint.
	{
		// Create the widget and store it.
		m_RaceHud = CreateWidget<UUserWidget>(this, wRaceWidget);

		// now you can use the widget directly since you have a referance for it.
		// Extra check to  make sure the pointer holds the widget.
		if (m_RaceHud)
		{
			//let add it to the view port
			m_RaceHud->AddToViewport();
		}
	}
}