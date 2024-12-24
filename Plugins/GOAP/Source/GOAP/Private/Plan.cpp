// Fill out your copyright notice in the Description page of Project Settings.


#include "Plan.h"

/* Only if the UObject has a reference to the world will fns like Delay be accessible via BP*/
UWorld* UPlan::GetWorld() const
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

void UPlan::InitializePlan(UBlackboardComponent* b)
{
	bbc = b;

	for (int i = 0;i < actionSpaceClasses.Num();i++)
	{
		// actionSpace.Add(NewObject<UAction>(this, actionSpaceClasses[i]->StaticClass())); using StaticClass gave an error as it didn't recognize child classes Reason: https://www.reddit.com/r/unrealengine/comments/ic6q9i/cannot_make_newobject_from_array_of_class/?rdt=57196
		actionSpace.Add(NewObject<UAction>(this, actionSpaceClasses[i]));
		// actionSpace[i]->Initialize(bbc); Should we initialize actions here or evertime they're called? or at a later pt?
	}
}

UAction* UPlan::PickAction()
{
	for (int i = 0;i < desiredWS.Num();i++)
	{
		if (desiredWS[i] == currWS[i]) { continue; }

		// Current implementation assumes only 1 action from possible actions give a desired WS. It returns that action
		// If needed modify it so that actions that return a desired WS are added to an array & then an action from the possiblity space is chosen
		for (int j = 0;j < actionSpace.Num();j++)
		{
			if (actionSpace[j]->WS == desiredWS[i]) { return actionSpace[j]; }
		}
		return nullptr;
	}

	return nullptr;
}