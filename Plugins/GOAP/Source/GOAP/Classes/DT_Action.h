// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DT_Action.generated.h"

/**
 * 
 */
UENUM(Blueprintable)
enum class EActionStatus :uint8
{
	AS_Invalid,
	AS_InProgress,
	AS_Success,
	AS_Fail,
	AS_OutOfSteps UMETA(Hidden)
};

UCLASS()
class GOAP_API UDT_Action : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
		FText ActionDesc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EActionStatus actionStatus;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int maxStepCount;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int currStep = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int currStepCount = 0;

	UPROPERTY(EditAnywhere)
		TArray<UDT_Action*> OnSuccess;
	UPROPERTY(EditAnywhere)
		TArray<UDT_Action*> OnFail;

	UBlackboardComponent* bbc;

	UFUNCTION(BlueprintCallable)
		virtual void InitializeAction(UBlackboardComponent* blackboardComp) { bbc = blackboardComp; }
	UFUNCTION(BlueprintCallable)
		virtual bool IsActionValid() { return false; }
	UFUNCTION(BlueprintCallable)
		virtual void Execute(){}
	UFUNCTION(BlueprintCallable)
		virtual float GetDelay() { return 0.1f; }
	UFUNCTION(BlueprintCallable)
		UDT_Action* NextAction();
	UFUNCTION()
		UDT_Action* FindValidAction(TArray<UDT_Action*> &listOfActions);
};
