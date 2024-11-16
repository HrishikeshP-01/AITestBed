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

/* We use EditInlineNew for branches because branches aren't that reusable.
 so we don't want them sitting around as assets.
 You can create branch assets if you want to but generally they don't have to be reused. 
 Just because you used EditInlineNew doesn't mean an asset can't be created, they can. This just allows us to define this class here itself*/
UCLASS(EditInlineNew)
class STATEMACHINE_API UFSM_Branch : public UDataAsset
{
	GENERATED_BODY()
public:
	/* A branch tells us whether or not we reached the destination state
	We want to know if it got to the destination state & what is the destination state.
	Instead of using 2 variables for these we can just ask it to return the DestinationState if it succeeds & NULL if it fails
	*/
	// If you want to create a branch with multiple inputs you can set the OutDataIndex to use something other than 1
	virtual UFSM_State* TryBranch(const UObject* refObject, const TArray<UFSM_InputAtom*>& DataSource,
		int32 DataIndex, int32& OutDataIndex);
protected:
	// State where this branch will go next. If it's null the branch is ignored
	UPROPERTY(EditAnywhere)
		UFSM_State* DestinationState;
	// If true, the meaning of AcceptableInputs is reversed
	UPROPERTY(EditAnywhere)
		uint32 bReverseInputTest : 1;
	// Acceptable inputs. Current input atom must be on this list
	UPROPERTY(EditAnywhere)
		TArray<UFSM_InputAtom*> AcceptableInputs;
};


UCLASS()
class STATEMACHINE_API UFSM_State : public UDataAsset
{
	GENERATED_BODY()
	
};
