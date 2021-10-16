// Copyright Epic Games, Inc. All Rights Reserved.

#include "TutorialPurposesGameMode.h"
#include "TutorialPurposesCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATutorialPurposesGameMode::ATutorialPurposesGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
