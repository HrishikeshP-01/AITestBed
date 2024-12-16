// Fill out your copyright notice in the Description page of Project Settings.


#include "Action.h"

/* Only if the UObject has a reference to the world will fns like Delay be accessible via BP*/
UWorld* UAction::GetWorld() const
{
	//Return null if the called from the CDO, or if the outer is being destroyed
	if (!HasAnyFlags(RF_ClassDefaultObject) && !GetOuter()->HasAnyFlags(RF_BeginDestroyed) && !GetOuter()->IsUnreachable())
	{
		//Try to get the world from the owning actor if we have one
		AActor* Outer = GetTypedOuter<AActor>();
		if (Outer != nullptr)
		{
			return Outer->GetWorld();
		}
	}
	//Else return null - the latent action will fail to initialize
	return nullptr;
}

bool UAction::IsValid()
{
	return false;
}

UAction* UAction::NextAction()
{
	if (actionCompletion == EActionCompletion::EAC_Succeeded)
	{
		for (int i = 0; i < OnSuccess.Num();i++)
		{
			if (OnSuccess[i]->IsValid()) { return OnSuccess[i]; }
		}
	}
	if (actionCompletion == EActionCompletion::EAC_Failed)
	{
		for (int i = 0;i < OnFail.Num();i++)
		{
			if (OnFail[i]->IsValid()) { return OnFail[i]; }
		}
	}
	// If in progress return the current action.
	// CONCERN: Will this cause the action to repeat?
	if (actionCompletion == EActionCompletion::EAC_InProgress) { return this; }

	// If invalid
	return nullptr;
}