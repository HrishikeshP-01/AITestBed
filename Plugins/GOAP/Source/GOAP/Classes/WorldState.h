// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WorldState.generated.h"

/**
 * 
 */
UENUM(Blueprintable)
enum class EWorldState :uint8
{
	// Proximity to target
	Proximity_Far,
	Proximity_MidRange,
	Proximity_CloseRange,

	// Item pick status
	Item_Equipped,
	Item_Unequipped,

	// Attack status
	Attack_InProgress,
	Attack_NotAttacking
};

UENUM(Blueprintable)
enum class EHandStatus :uint8
{
	NoHands,
	LeftHandOnly,
	RightHandOnly,
	BothHands
};