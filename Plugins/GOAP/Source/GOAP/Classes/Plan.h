// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action.h"
#include "WorldState.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Plan.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class GOAP_API UPlan : public UObject
{
	GENERATED_BODY()
	
	virtual UWorld* GetWorld() const override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<EWorldState> desiredWS;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<EWorldState> currWS;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<TSubclassOf<UAction>> actionSpaceClasses;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<UAction*> actionSpace;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBlackboardComponent* bbc;

	UFUNCTION(BlueprintCallable)
		virtual void InitializePlan(UBlackboardComponent* b);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = Gameplay)
		void CalculateCurrWS();
	UFUNCTION(BlueprintCallable)
		UAction* PickAction();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = Gameplay)
		void ExecuteStep();
};
