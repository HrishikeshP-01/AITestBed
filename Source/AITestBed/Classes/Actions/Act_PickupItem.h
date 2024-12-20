// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DT_Action.h"
#include "GameFramework/Character.h"
#include "Act_PickupItem.generated.h"

/**
 * 
 */
UCLASS()
class AITESTBED_API UAct_PickupItem : public UDT_Action
{
	GENERATED_BODY()
	
public:
	virtual void InitializeAction(UBlackboardComponent* blackboardComp) override;
	virtual bool IsActionValid() override;

	// Replace class type with respective class once created. Will need casting so consider using interfaces instead
	// For actions like this the overhead might be small as we cast once & store in variable
	AActor* item;
	ACharacter* player;
};
