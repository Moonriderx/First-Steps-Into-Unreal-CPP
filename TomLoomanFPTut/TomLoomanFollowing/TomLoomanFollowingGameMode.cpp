// Copyright Epic Games, Inc. All Rights Reserved.

#include "TomLoomanFollowingGameMode.h"
#include "TomLoomanFollowingHUD.h"
#include "TomLoomanFollowingCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATomLoomanFollowingGameMode::ATomLoomanFollowingGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ATomLoomanFollowingHUD::StaticClass();
}
