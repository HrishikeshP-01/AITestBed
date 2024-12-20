// Fill out your copyright notice in the Description page of Project Settings.


#include "DT_Action.h"

UDT_Action* UDT_Action::NextAction()
{
	switch (actionStatus)
	{
	case EActionStatus::AS_Success:
		return FindValidAction(OnSuccess);
	case EActionStatus::AS_Fail:
		return FindValidAction(OnFail);
	case EActionStatus::AS_InProgress:
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
