// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/MoveTo.h"

void UMoveTo::Initialize(UBlackboardComponent* b)
{
	Super::Initialize(b);

	grid = Cast<AGrid>(bbc->GetValueAsObject(FName("Grid")));
}

bool UMoveTo::IsValid()
{
	// return true for now, can't figure out what the false condition would be. No limbs?
	return true;
}

FVector UMoveTo::MoveToPos(const FVector& currPos, const FVector& targetPos)
{
	// Check if already at destination
	if (grid->GetTileIndexFromLocation(currPos) == grid->GetTileIndexFromLocation(targetPos))
	{
		actionStatus = EActionStatus::EAS_Succeeded;
		UE_LOG(LogTemp, Log, TEXT("Action: MoveTo Result: Reached target"));
		return currPos;
	}

	// Right now we are assuming that there are no obstacles at targetPos
	// If needed add logic to check if targetPos is occupied & get neighboring node & chart a path to the neighboring node instead

	// Assuming a path exists
	TArray<FVector> path; //= grid->ReturnPath(currPos, targetPos);
	grid->GetPath(currPos, targetPos, path);
	UE_LOG(LogTemp, Log, TEXT("Action: MoveTo Result: Grid Actor- %s"), grid->GetDebugName);

	grid->VisualizePath(path, true, 1.0f, FColor::Red);

	if (path.Num() < 2)
	{
		UE_LOG(LogTemp, Log, TEXT("Action: MoveTo Result: Path doesn't exist Path length: %d"),path.Num());

		actionStatus = EActionStatus::EAS_Failed;
		return FVector::Zero();
	}

	actionStatus = EActionStatus::EAS_InProgress;
	return path[path.Num() - 2];
}