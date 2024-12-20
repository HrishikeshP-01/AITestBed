// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grid.generated.h"

USTRUCT(Blueprintable)
struct GOAP_API FTileInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector location;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float cost;
	
	TArray<FTileInfo*> neighbors;

	FTileInfo* GetNeighbor(int i)
	{
		return neighbors[i];
	}

	void SetNeighbor(FTileInfo* n)
	{
		neighbors.Add(n);
	}
};


UCLASS()
class GOAP_API AGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrid();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FTileInfo> tiles;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int tile_X = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int tile_Y = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Side = 10.0;

	UFUNCTION(BlueprintCallable)
		void GetGridIndex(const FVector& location, int& X, int& Y);
	UFUNCTION(BlueprintCallable)
		int GetTileIndex(int X, int Y);

	// Debug
	UFUNCTION(BlueprintCallable)
		void DrawGrid();

	// Pathfinding
	UFUNCTION(BlueprintCallable)
		void GetPath(const FVector& start, const FVector& end, TArray<FVector>& path);
	void AddNeighbor(TSet<int>& closedIndices, TArray<FVector>& open, int n, int f_cost, int parentIndex);

};
