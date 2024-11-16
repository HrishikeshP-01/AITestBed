// Fill out your copyright notice in the Description page of Project Settings.


#include "FSM_State.h"

/*The branch only consumes 1 unit of data at a time. If you want you can modify it to consume additional units.
This is useful in a scenario such as a fighting game where pressing a button 3 times will lead to a different state*/
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

UFSM_State::UFSM_State()
{
	bLoopByDefault = true;
}

FStateMachineResult UFSM_State::RunState(const UObject* refObject, const TArray<UFSM_InputAtom*>& DataSource,
	int32 DataIndex /*= 0*/, int32 RemainingSteps /*= -1*/)
{
	// If the state reached says to terminate immediately or if the data index exceeds the length of the data source array
	bool bMustEndNow = (bTerminateImmediately || !DataSource.IsValidIndex(DataIndex));

	// If it's still running see where the branches lead
	if (!bMustEndNow && RemainingSteps)
	{
		UFSM_State* DestinationState = nullptr;
		int32 DestinationDataIndex = DataIndex;
		for (int i = 0;i < InstancedBranches.Num();i++)
		{
			/*We could use check or ensure instead of if
			check(InstancedBranches[i]);
			But this will crash the game & modified files in editor will be lost
			using ensure won't crash the game & will also throw a one-time warning(every time a new instance of the editor is started)
			Problem with if is it won't tell you if InstancedBranches is NULL unless you explicitly write debug logic*/
			if (InstancedBranches[i])
			{
				DestinationState = InstancedBranches[i]->TryBranch(refObject, DataSource, DataIndex, DestinationDataIndex);
				if (DestinationState) // If the branch returned a destination state
				{
					return DestinationState->RunState(refObject, DataSource, DestinationDataIndex, RemainingSteps - 1);
				}
			}
		}
		// If we didn't find any acceptable branch we end on this state unless we're told to loop
		if (bLoopByDefault)
		{
			return Loop(refObject, DataSource, DataIndex, RemainingSteps);
		}
		bMustEndNow = true;
	}

	/*We can make a constructor for FStateMachineResult which is a safer way to ensure necessary params are set*/
	FStateMachineResult SMR;
	SMR.FinalState = this;
	SMR.DataIndex = DataIndex;
	// bMustEndNow = true means no other acceptable branches are remaining & this is the destination state
	// if bMustEndNow = false & we still reached here means we run out of steps
	SMR.CompletionType = bMustEndNow ? CompletitionType : EStateMachineCompletionType::OutOfSteps;

	return SMR;
}

FStateMachineResult UFSM_State::Loop(const UObject* refObject, const TArray<UFSM_InputAtom*>& DataSource,
	int32 DataIndex, int32 RemainingSteps)
{
	/* By default increase data index by 1 & decrease remaining steps by 1
	 increase data index to go to the next input
	 decrease remaining steps bc say you have 50 unaccaptable inputs 
	 & you go through them without decreasing remaining steps
	this wastes resources especially when garbage values are present in your input. */
	return RunState(refObject, DataSource, DataIndex + 1, RemainingSteps - 1);
}