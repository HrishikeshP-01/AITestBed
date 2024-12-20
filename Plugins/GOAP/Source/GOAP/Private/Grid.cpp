// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid.h"
#include "DrawDebugHelpers.h"

// Sets default values
AGrid::AGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGrid::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGrid::GetGridIndex(const FVector& location, int& X, int& Y)
{
	X = FMath::Floor((location - GetActorLocation()).X / Side);
	Y = FMath::Floor((location - GetActorLocation()).Y / Side);
}

int AGrid::GetTileIndex(int X, int Y)
{
	return (Y * tile_X) + X;
}

void AGrid::DrawGrid()
{
	UWorld* world = GetWorld();
	for (int i = 0;i < tiles.Num();i++)
	{
		DrawDebugBox(world, tiles[i].location, FVector(Side, Side, Side) / 2, FColor::MakeRedToGreenColorFromScalar(1-tiles[i].cost), true);
	}
}

void AGrid::GetPath(const FVector& start, const FVector& end, TArray<FVector>& path)
{
	int X = FMath::Floor((start - GetActorLocation()).X / Side);
	int Y = FMath::Floor((start - GetActorLocation()).Y / Side);
	int startIndex = GetTileIndex(X, Y);
	X = FMath::Floor((end - GetActorLocation()).X / Side);
	Y = FMath::Floor((end - GetActorLocation()).Y / Side);
	int endIndex = GetTileIndex(X, Y);

	DrawDebugSphere(GetWorld(), start, 30.0f, 5, FColor::Red, true);
	DrawDebugSphere(GetWorld(), end, 30.0f, 5, FColor::Green, true);
	DrawDebugSphere(GetWorld(), tiles[startIndex].location, 30.0f, 3, FColor::Purple, true);
	DrawDebugSphere(GetWorld(), tiles[endIndex].location, 30.0f, 3, FColor::Yellow, true);
	UE_LOG(LogTemp, Warning, TEXT("Grid start: %d"), startIndex);
	UE_LOG(LogTemp, Warning, TEXT("Grid end: %d"), endIndex);

	TArray<FVector> open;
	TArray<FVector> closed;
	TSet<int> closedIndices;
	int parentIndex = -1;

	open.Add(FVector((float)startIndex, tiles[startIndex].cost, (float)parentIndex));
	
	
	while (open.Num() > 0)
	{

		float minCost = open[0].Y + FVector::DistSquared(end, tiles[open[0].X].location);
		int minCostNode = 0;
		for (int i = 0;i < open.Num();i++)
		{
			UE_LOG(LogTemp, Warning, TEXT("Grid Open: %s"), *open[minCostNode].ToString());
			if (open[i].Y + FVector::DistSquared(end, tiles[open[i].X].location) < minCost)
			{
				minCost = open[i].Y + FVector::DistSquared(end, tiles[open[i].X].location);
				minCostNode = i;
			}
		}

		open[minCostNode].Z = parentIndex;
		++parentIndex;
		closed.Add(open[minCostNode]);

		// Check if the node is destination
		if (closed[parentIndex].X == endIndex)
		{
			FVector p = closed[parentIndex];
			while (p.Z != -1)
			{
				path.Push(tiles[p.X].location);
				p = closed[p.Z];
			}
			path.Push(tiles[startIndex].location);
			return;
		}

		UE_LOG(LogTemp, Warning, TEXT("Grid Adding Neighbors"));

		closedIndices.Add(open[minCostNode].X);
		// Add neighbors of the tile to open if not already closed
		if ((int)open[minCostNode].X % tile_X != 0)
		{
			AddNeighbor(closedIndices, open, open[minCostNode].X - 1, open[minCostNode].Y, parentIndex);
		}
		if ((int)open[minCostNode].X % tile_X != tile_X - 1)
		{
			AddNeighbor(closedIndices, open, open[minCostNode].X + 1, open[minCostNode].Y, parentIndex);
		}
		if ((int)open[minCostNode].X - tile_X >= 0)
		{
			AddNeighbor(closedIndices, open, open[minCostNode].X - tile_X, open[minCostNode].Y, parentIndex);
		}
		if ((int)open[minCostNode].X + tile_X < tile_X * tile_Y)
		{
			AddNeighbor(closedIndices, open, open[minCostNode].X + tile_X, open[minCostNode].Y, parentIndex);
		}
		open.RemoveAt(minCostNode);
	}

}

void AGrid::AddNeighbor(TSet<int>& closedIndices, TArray<FVector>& open, int n, int f_cost, int parentIndex)
{
	if (closedIndices.Contains(n)) { return; }
	if (tiles[n].cost > 0.9) { return; } // Is an obstacle

	open.Add(FVector(n, tiles[n].cost + f_cost, parentIndex));
	UE_LOG(LogTemp, Warning, TEXT("Grid Added neighbor: %d"), n);
}