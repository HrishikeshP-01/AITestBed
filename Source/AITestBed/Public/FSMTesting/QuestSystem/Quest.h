// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Quest.generated.h"

/**
 * A Quest is a FSM & it has it's own states
 */

// States a quest can have
UENUM(Blueprintable)
enum class EQuestCompletion
{
	EQC_NotStarted,
	EQC_Started,
	EQC_Succeeded,
	EQC_Failed
};

UCLASS()
class AITESTBED_API UQuest : public UDataAsset
{
	GENERATED_BODY()
	
};
