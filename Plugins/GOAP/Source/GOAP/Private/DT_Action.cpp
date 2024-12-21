// Fill out your copyright notice in the Description page of Project Settings.


#include "DT_Action.h"

UDT_Action* UDT_Action::NextAction()
{
	switch (actionStatus)
	{
	case EDTActionStatus::AS_Success:
		return FindValidAction(OnSuccess);
	case EDTActionStatus::AS_Fail:
		return FindValidAction(OnFail);
	case EDTActionStatus::AS_InProgress:
		return this;
	}

	return nullptr;
}

UDT_Action* UDT_Action::FindValidAction(TArray<UDT_Action*> &listOfActions)
{
	for (int i = 0;i < listOfActions.Num();i++)
	{
		if (listOfActions[i]->IsActionValid()) { return listOfActions[i]; }
	}
	return nullptr;
}
