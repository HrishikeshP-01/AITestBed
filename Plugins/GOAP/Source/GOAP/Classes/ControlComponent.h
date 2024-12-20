// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Action.h"
#include "DT_Action.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ControlComponent.generated.h"


UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GOAP_API UControlComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UControlComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		uint32 bIsBeingObserved : 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UAction> currActionClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UDT_Action* currAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBlackboardComponent* bbc;
		
};
