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

	InitializeSteps();
}

UAction* UPlan::PickAction()
{
	for (counter = 0;counter < desiredWS.Num();counter++)
	{
		if (desiredWS[counter] == currWS[counter]) { continue; }

		// Current implementation assumes only 1 action from possible actions give a desired WS. It returns that action
		// If needed modify it so that actions that return a desired WS are added to an array & then an action from the possiblity space is chosen
		for (int j = 0;j < actionSpace.Num();j++)
		{
			if (actionSpace[j]->WS == desiredWS[counter]) { return actionSpace[j]; }
		}
		return nullptr;
	}

	return nullptr;
}

void UPlan::ExitPlan_Implementation()
{
	// At this point I'm not sure if I need to know the plan completion status so I'm not implementing logic for it. For now the delegate only returns the next plan if any
	TSubclassOf<UPlan> nextPlan = ExitSteps();
	PlanCompletedDelegate.Broadcast(nextPlan);

	// PlanCompleteDelegate.Execute(nextPlan, false); non-multi cast delegate isn't blueprint assingable & throws a not bound error for some reason

	//// if the desiredWS = currWS then the plan has succeeded
	//if (counter >= desiredWS.Num())
	//{
	//	PlanCompleteDelegate.Execute(nullptr, true);
	//}
	//
	//// if the counter isn't complete it says plan failed. Review
	//PlanCompleteDelegate.Execute(nullptr, false);
	
}