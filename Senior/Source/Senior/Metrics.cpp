// Fill out your copyright notice in the Description page of Project Settings.

#include "Metrics.h"


// Sets default values for this component's properties
UMetrics::UMetrics()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UMetrics::BeginPlay()
{
	Super::BeginPlay();

	// ..
	StartGame();
}


// Called every frame
void UMetrics::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void UMetrics::GetTime(FDateTime &current)
{
	current = current.Now();
}


void UMetrics::EndTime(FDateTime &start, FTimespan &puzzleTime)
{
	FDateTime end = end.Now();
	puzzleTime = end - start;
}


void UMetrics::StartGame()
{
	GetTime(Date);
}


void UMetrics::EndGame()
{
	UE_LOG(LogTemp, Warning, TEXT("Date                  Player ID   Puzzle 1   Puzzle 2   Puzzle 3\n"));
	UE_LOG(LogTemp, Warning, TEXT("%-22s%-12d%-11.2f%-11.2f%-11.2f\n"), *Date.ToString(), PlayerID, Puzzle1Time.GetTotalMinutes(), Puzzle2Time.GetTotalMinutes(), Puzzle3Time.GetTotalMinutes());
}


void UMetrics::EnteredRoom(FString room)
{
	if (room == "IF")
	{
		// Display IF puzzle info
		GetTime(Start);
	}
	if (room == "ARR")
	{
		// Display ARR puzzle info
		GetTime(Start);
	}
	if (room == "FOR")
	{
		// Display FOR puzzle info
		GetTime(Start);
	}
	if (room == "Prize")
	{
		// Display Prize info
	}
}


void UMetrics::PuzzleSolved(FString room)
{
	if (room == "IF")
	{
		EndTime(Start, Puzzle1Time);
		// Update HUD Level
	}
	if (room == "ARR")
	{
		EndTime(Start, Puzzle2Time);
		// Update HUD Level
	}
	if (room == "FOR")
	{
		EndTime(Start, Puzzle3Time);
		// Update HUD Level
	}
}

void UMetrics::CreateJSON(int32 id, FDateTime GameDate, FRoom roomOne, FRoom roomTwo, FRoom roomThree, FDateTime GameStarted, FDateTime GameEnded, TArray<FPlayerPath> pPath)
{
	//TODO create json object
	//TODO Call Printer
	return;
}

void FileWritter(FString JSONObject)
{
	//TODO Print to file
	return;
}