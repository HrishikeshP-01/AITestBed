// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/Act_PickupItem.h"

void UAct_PickupItem::InitializeAction(UBlackboardComponent* blackboardComp)
{
	Super::InitializeAction(blackboardComp);

	const FName playerKey = FName("Player");
	const FName itemKey = FName("Item");

	//int x = (bbc->GetValueAsInt(playerKey));
	//item = Cast<AActor>(bbc->GetValueAsObject(itemKey));
}

bool UAct_PickupItem::IsActionValid()
{
	// check if item is valid
	if (!item) { return false; }
	// check if player is near item
	// Using dummy threshold, store the threshold with item & get it from there as theshold could be different for each item
	if (FVector::Distance(player->GetActorLocation(), item->GetActorLocation()) > 0.5f) { return false; }
	return true;
}