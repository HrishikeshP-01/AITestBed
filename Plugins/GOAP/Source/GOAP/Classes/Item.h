// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Plan.h"
#include "Item.generated.h"

UCLASS()
class GOAP_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Use interfaces during actual implementation
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UPlan> plan;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName SocketName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isBeingUsed;

};
