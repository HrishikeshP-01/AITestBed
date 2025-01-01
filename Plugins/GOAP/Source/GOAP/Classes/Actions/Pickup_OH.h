// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action.h"
#include "Item.h"
#include "Pickup_OH.generated.h"

/**
 * 
 */
UCLASS()
class GOAP_API UPickup_OH : public UAction
{
	GENERATED_BODY()

public:
	virtual void Initialize(UBlackboardComponent* b)override;
	virtual bool IsValid()override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AItem* item;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float itemPickupRange = 100.0f;
	/*void Execute()override;*/
	
};
