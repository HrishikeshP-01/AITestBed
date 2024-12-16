// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "Action.generated.h"

/**
 * 
 */
UENUM(Blueprintable)
enum class EActionCompletion :uint8
{
	EAC_Invalid, // If the action becomes invalid 
	EAC_InProgress,
	EAC_Succeeded,
	EAC_Failed
};


UCLASS(Blueprintable)
class GOAP_API UAction : public UObject
{
	GENERATED_BODY()

	virtual UWorld* GetWorld() const override;

public:
	UFUNCTION(BlueprintCallable)
		// Fn that returns true if an action is valid
		virtual bool IsValid();
	UFUNCTION(BlueprintImplementableEvent)
		// Execute is an event so designers can access it via BP & use nodes like Delay
		void Execute();

	// Fn to find the next action to be taken. First valid action from the list will be executed
	UAction* NextAction();

	UPROPERTY(EditAnywhere)
		TArray<UAction*> OnSuccess; // List of actions to be taken upon success in decreasing order of priority
	UPROPERTY(EditAnywhere)
		TArray<UAction*> OnFail; // List of actions to be taken upon failure in decreasing order of priority
	UPROPERTY(EditAnywhere)
		EActionCompletion actionCompletion; // Completion status of current action

	// Testing. Remove uneccesary code once done
	UPROPERTY(EditAnywhere)
		UBlackboardComponent* x;
	UPROPERTY(EditAnywhere)
		UBlackboardData* y;

	// Debug
	UPROPERTY(EditAnywhere)
		FText desc;
};
