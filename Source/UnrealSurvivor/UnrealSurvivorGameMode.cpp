// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealSurvivorGameMode.h"
#include "UnrealSurvivorCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUnrealSurvivorGameMode::AUnrealSurvivorGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
