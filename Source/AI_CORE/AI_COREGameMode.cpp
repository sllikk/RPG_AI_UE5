// Copyright Epic Games, Inc. All Rights Reserved.

#include "AI_COREGameMode.h"
#include "AI_COREPlayerController.h"
#include "AI_CORECharacter.h"
#include "UObject/ConstructorHelpers.h"

AAI_COREGameMode::AAI_COREGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AAI_COREPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}