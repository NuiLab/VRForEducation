// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Core/Public/Misc/DateTime.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "Metrics.generated.h"

USTRUCT()
struct FRoom {
	//GENERATED_USTRUCT_BODY()
	GENERATED_USTRUCT_BODY()

	FDateTime enterRoom;
	FDateTime startPuzzle;
	FDateTime solvePuzzle;
	FDateTime exitRoom;
	int32 TotalTries;
};

USTRUCT()
struct FPlayerPath {
	GENERATED_USTRUCT_BODY()
	//GENERATED_BODY()

	FVector PlayerLocation;
	FRotator PlayerRotation;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SENIOR_API UMetrics : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMetrics();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Game Event")
		void StartGame();

	UFUNCTION(BlueprintCallable, Category = "Game Event")
		void EndGame();

	UFUNCTION(BlueprintCallable, Category = "Game Event")
		void EnteredRoom(FString room);

	UFUNCTION(BlueprintCallable, Category = "Game Event")
		void PuzzleSolved(FString room);

	void GetTime(FDateTime &current);

	void EndTime(FDateTime &start, FTimespan &puzzleTime);

	void CreateJSON(int32 id, FDateTime GameDate, FRoom roomOne, FRoom roomTwo, FRoom roomThree, FDateTime GameStarted, FDateTime GameEnded, TArray<FPlayerPath> pPath);

	void FileWritter(FString JSONObject);

private:
	// Metrics
	FTimespan Puzzle1Time;
	FTimespan Puzzle2Time;
	FTimespan Puzzle3Time;
	FDateTime Start;
	FDateTime Date;
	const int PlayerID = 10;

};