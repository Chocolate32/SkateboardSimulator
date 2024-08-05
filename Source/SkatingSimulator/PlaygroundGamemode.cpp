// Fill out your copyright notice in the Description page of Project Settings.


#include "PlaygroundGamemode.h"

APlaygroundGamemode::APlaygroundGamemode()
{
	static ConstructorHelpers::FClassFinder<APawn> BP_SkateCharacter(TEXT("/Game/Blueprints/Characters/BP_SkateCharacter"));
	if (BP_SkateCharacter.Class != NULL) {
		DefaultPawnClass = BP_SkateCharacter.Class;
	}
	else
		DefaultPawnClass = ASkateCharacter::StaticClass();
}
