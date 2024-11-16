// Fill out your copyright notice in the Description page of Project Settings.


#include "FSM_State.h"

UFSM_State* UFSM_Branch::TryBranch(const UObject* refObject, const TArray<UFSM_InputAtom*>& DataSource,
	int32 DataIndex, int32& OutDataIndex)
{
	OutDataIndex = DataIndex;
	if (!AcceptableInputs.Num() // If acceptable inputs is not empty
		|| DataSource.IsValidIndex(DataIndex) // If DataSource contains an element at the given data index
		&& AcceptableInputs.Contains(DataSource[DataIndex]) // If input at that particular position is present in AcceptableInputs
		)
	{
		++OutDataIndex;
		return (bReverseInputTest ? nullptr : DestinationState);
	}

	return (bReverseInputTest ? DestinationState : nullptr);
}