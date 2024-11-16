// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FSM_State.h"
#include "Quest.generated.h"

/**
 * A Quest is a FSM & it has it's own states
 */

// States a quest can have
UENUM(Blueprintable)
enum class EQuestCompletion : uint8
{
	EQC_NotStarted,
	EQC_Started,
	EQC_Succeeded,
	EQC_Failed
};

/*We are going to have a master list of everything we do in-game 
& each input atom from this master list gets added to the quest's data source
only if the quest is active & if the action is present in the input list of each quest (or not depending on bIsBlackList)*/
UCLASS()
class AITESTBED_API UQuest : public UDataAsset
{
	GENERATED_BODY()
	
public:
	/*Name of the quest, this can be used to display the quest name to player
	Use FText wherever you want to display stuff to player as this is localizable
	*/
	UPROPERTY(EditAnywhere)
		FText QuestName;
	// If this machine accepts our Quest Activities log, the quest is successful
	UPROPERTY(EditAnywhere)
		UFSM_State* QuestStateMachine;
	/*If true the input list is a blacklist i.e, list of actions which are not part of the quest
	if false it's a whitelist, list of actions that are part of the quest*/
	UPROPERTY(EditAnywhere)
		uint32 bIsBlackList : 1;
	/*If bIsBlackList=true then all actions in this list are not part of the quest & will be ignored
	else all actions in this list are part of the quest & only these will be considered*/
	UPROPERTY(EditAnywhere)
		TArray<UFSM_InputAtom*> ValidInputList;

};

USTRUCT()
struct FQuestInProgress
{
	GENERATED_BODY()
	// Quest data asset
	UPROPERTY(EditAnywhere)
		const UQuest* Quest;
	// const used because UQuest is a data asset & generally we don't modify data asset values during execution
	
	// Current progress in the quest
	UPROPERTY(EditAnywhere)
		EQuestCompletion QuestProgress;

protected:
	// All input for this quest which is obtained from master input list after filtering using whitelist/blacklist
	TArray<UFSM_InputAtom*> QuestActivities;

public:
	// returns true if the quest was completed (success or failed) or false if it's still in progress
	bool UpdateQuest(const UObject* refObject, UFSM_InputAtom* QuestActivity)
	{
		/*We will add this particular quest activity only if the quest has started
		and only if this activity is inside the whitelist (outside blacklist)*/
		if (Quest && (QuestProgress == EQuestCompletion::EQC_Started)
			&& Quest->bIsBlackList != Quest->ValidInputList.Contains(QuestActivity))
		{
			FStateMachineResult QuestResult;
			QuestActivities.Add(QuestActivity);
			QuestResult = Quest->QuestStateMachine->RunState(refObject, QuestActivities);

			switch (QuestResult.CompletionType)
			{
			case EStateMachineCompletionType::Accepted:
				QuestProgress = EQuestCompletion::EQC_Succeeded;
				return true;
			case EStateMachineCompletionType::Rejected:
				QuestProgress = EQuestCompletion::EQC_Failed;
				return true;
			// case EStateMachineCompletionType::NotAccepted means it's still in progress no update to QuestProgress needed
			}
		}
		return false;
	}
};