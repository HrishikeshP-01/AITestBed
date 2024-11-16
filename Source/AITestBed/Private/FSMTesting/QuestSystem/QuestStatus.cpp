// Fill out your copyright notice in the Description page of Project Settings.


#include "FSMTesting/QuestSystem/QuestStatus.h"

// Sets default values for this component's properties
UQuestStatus::UQuestStatus()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UQuestStatus::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UQuestStatus::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UQuestStatus::UpdateQuest(UFSM_InputAtom* QuestActivity)
{
	// Add the quest activity to the master list
	MasterQuestActivityList.Add(QuestActivity);

	// Update individual quests (the quest will check if they care about the newly added activity) & see if they have been completed
	for (int32 i = 0;i < ActiveQuests.Num();i++)
	{
		if (ActiveQuests[i].UpdateQuest(this, QuestActivity))
		{
			// if it returns true it means quest has completed
			UE_LOG(LogTemp, Log, TEXT("QuestSystem: Quest \"%s\" completed: %s"),
				*ActiveQuests[i].Quest->QuestName.ToString(),
				(ActiveQuests[i].QuestProgress == EQuestCompletion::EQC_Succeeded) ? TEXT("Succeeded") : TEXT("Failed"));
		}
	}
}
