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

DECLARE_DYNAMIC_DELEGATE_TwoParams(FPlanCompleteSignature, TSubclassOf<UPlan>, nextPlan, bool, planSucceeded);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlanCompletedSignature, TSubclassOf<UPlan>, nextPlan);

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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int counter;

	//UPROPERTY(BlueprintAssignable) only for multi-cast. Idt we need multi-cast delegate for plans
	FPlanCompleteSignature PlanCompleteDelegate;
	UPROPERTY(BlueprintAssignable)
		FPlanCompletedSignature PlanCompletedDelegate;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void InitializeSteps();
	UFUNCTION(BlueprintCallable)
		virtual void InitializePlan(UBlackboardComponent* b);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = Gameplay)
		void CalculateCurrWS();
	UFUNCTION(BlueprintCallable)
		UAction* PickAction();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = Gameplay)
		void ExecuteStep();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		TSubclassOf<UPlan> ExitSteps();
	// We no longer need exit plan to be an event. Just make it a fn. We are handling custom logic in exit steps fn anyways
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void ExitPlan();
};
