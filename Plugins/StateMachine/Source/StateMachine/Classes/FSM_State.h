// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FSM_State.generated.h"

/**
 * 
 */
UENUM()
enum class EStateMachineCompletionType : uint8
{
	// Implicit failure, this state is not marked as Accepted
	NotAccepted,
	// Success, this state is marked as Accepted
	Accepted,
	// Explicit failure, this state is specifically marked as NotAccepted or Failure
	Rejected,
	// The simulation ran out of steps while the machine was still running
	OutOfSteps UMETA(Hidden) // Hidden means that player can't set the value to this in BP
};

USTRUCT()
struct STATEMACHINE_API FStateMachineResult
{
	GENERATED_BODY()

	UPROPERTY()
		EStateMachineCompletionType CompletionType;
	UPROPERTY()
		UFSM_State* FinalState; // The actual state we ended on
		// We store FinalState so that if the run hasn't ended, we can easily pick up where we left off
	UPROPERTY()
		int32 DataIndex; // Array of inputs

};

/* A class that represents the most basic i.e, atomic level of input
 Instead of data assets we can use ints or FNames as inputs but:
 ints - require designers to use a lookup sheet everytime they need to enter inputs to the FSM
 FName - too error prone. Typos can lead to the game breaking. */
UCLASS()
class STATEMACHINE_API UFSM_InputAtom : public UDataAsset
{
	GENERATED_BODY()
public:
	// Let users add a description to the input which is easy to debug
	UPROPERTY(EditAnywhere)
		FName Description;
};

UCLASS()
class STATEMACHINE_API UFSM_State : public UDataAsset
{
	GENERATED_BODY()
	
};
