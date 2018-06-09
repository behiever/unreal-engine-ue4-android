// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>

#define LogDebug(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1000, FColor::Blue,text)
#define LogError(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1000, FColor::Red,text)
/**
 * 
 */
