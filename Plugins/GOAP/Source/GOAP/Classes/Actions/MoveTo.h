// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action.h"
#include <GOAP/Classes/Grid.h>
#include "MoveTo.generated.h"


/**
 * 
 */
UCLASS()
class GOAP_API UMoveTo : public UAction
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AGrid* grid;
	virtual void Initialize(UBlackboardComponent* b) override;
	UFUNCTION(BlueprintCallable)
		FVector MoveToPos(const FVector& currPos, const FVector& targetPos);
};
