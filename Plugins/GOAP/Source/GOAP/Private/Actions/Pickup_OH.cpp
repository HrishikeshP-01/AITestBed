// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/Pickup_OH.h"

void UPickup_OH::Initialize(UBlackboardComponent* b)
{
	Super::Initialize(b);

	item = Cast<AItem>(bbc->GetValueAsObject(FName("Target")));
}

bool UPickup_OH::IsValid()
{
	// Check if the bot has hands
	EHandStatus hs = static_cast<EHandStatus>(bbc->GetValueAsEnum(FName("HandStatus")));
	if (hs == EHandStatus::NoHands) { return false; }

	//// Do we need to Check if item is within range as we already do it in the move to fn
	//AActor* bot = Cast<AActor>(bbc->GetValueAsObject(FName("SelfActor")));
	//if (FVector::Distance(bot->GetActorLocation(), item->GetActorLocation()) > itemPickupRange) { return false; }
	// It would be good to add debug messages here so we know exactly where each action, plan, goal fails
	
	// If item is being used by someone, you can't pick it up
	if (item->isBeingUsed) { return false; }

	return true;
}

//void UPickup_OH::Execute()
//{
//	UObject* items[2];
//	// Consider changing them to enums? With item names so Shukracharya can keep track?
//	items[0] = bbc->GetValueAsObject(FName("Item_RH"));
//	items[1] = bbc->GetValueAsObject(FName("Item_LH"));
//
//	int hand = (FMath::RandRange(0.0f, 1.0f) > 0.5f)? 0 : 1;
//	
//	if (items[1 - hand])
//	{
//		if (items[hand])
//		{
//
//		}
//	}
//}