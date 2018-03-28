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


void UMetrics::GetDate(FDateTime &current)
{
	FDateTime date = date.Now();
	current = date.GetDate();
}


void UMetrics::GetTime(FTimespan &current)
{
	FDateTime time = time.Now();
	current = time.GetTimeOfDay();
}


void UMetrics::StartGame()
{
	GetDate(Date);
	GetTime(StartTime);
}


void UMetrics::EndGame()
{
	GetTime(EndTime);
	
	UE_LOG(LogTemp, Warning, TEXT("Date: %s\n"), *Date.ToString().LeftChop(9));
	UE_LOG(LogTemp, Warning, TEXT("Player ID: %d\n"), PlayerID);
	UE_LOG(LogTemp, Warning, TEXT("Game Started: %s\n"), *StartTime.ToString());
	UE_LOG(LogTemp, Warning, TEXT("        Room 1        Room 2        Room 3\n"));
	UE_LOG(LogTemp, Warning, TEXT("Enter:  %-14s%-14s%-14s\n"), *RoomOne.EnterRoom.ToString(), *RoomTwo.EnterRoom.ToString(), *RoomThree.EnterRoom.ToString());
	UE_LOG(LogTemp, Warning, TEXT("Start:  %-14s%-14s%-14s\n"), *RoomOne.StartPuzzle.ToString(), *RoomTwo.StartPuzzle.ToString(), *RoomThree.StartPuzzle.ToString());
	UE_LOG(LogTemp, Warning, TEXT("Solved: %-14s%-14s%-14s\n"), *RoomOne.SolvedPuzzle.ToString(), *RoomTwo.SolvedPuzzle.ToString(), *RoomThree.SolvedPuzzle.ToString());
	UE_LOG(LogTemp, Warning, TEXT("Exit:   %-14s%-14s%-14s\n"), *RoomOne.ExitRoom.ToString(), *RoomTwo.ExitRoom.ToString(), *RoomThree.ExitRoom.ToString());
	UE_LOG(LogTemp, Warning, TEXT("Tries:  %-14d%-14d%-14d\n"), RoomOne.TotalTries, RoomTwo.TotalTries, RoomThree.TotalTries);
	UE_LOG(LogTemp, Warning, TEXT("Game Ended: %s\n"), *EndTime.ToString());
}


void UMetrics::EnteredRoom(FString room)
{
	if (room == "IF")
	{
		GetTime(RoomOne.EnterRoom);
		// Display IF puzzle info
		//PuzzleStarted("IF");
	}
	if (room == "ARR")
	{
		GetTime(RoomOne.ExitRoom);
		GetTime(RoomTwo.EnterRoom);
		// Display ARR puzzle info
		//PuzzleStarted("ARR");
	}
	if (room == "FOR")
	{
		GetTime(RoomTwo.ExitRoom);
		GetTime(RoomThree.EnterRoom);
		// Display FOR puzzle info
		//PuzzleStarted("FOR");
	}
	if (room == "Prize")
	{
		GetTime(RoomThree.ExitRoom);
		// Display Prize info
	}
}


void UMetrics::PuzzleStarted(FString room)
{
	if (room == "IF")
	{
		GetTime(RoomOne.StartPuzzle);
	}
	if (room == "ARR")
	{
		GetTime(RoomTwo.StartPuzzle);
	}
	if (room == "FOR")
	{
		GetTime(RoomThree.StartPuzzle);
	}
}


void UMetrics::PuzzleSolved(FString room)
{
	if (room == "IF")
	{
		GetTime(RoomOne.SolvedPuzzle);
		RoomOne.TotalTries = ScaleUsed;
		// Update HUD Level
	}
	if (room == "ARR")
	{
		GetTime(RoomTwo.SolvedPuzzle);
		//RoomTwo.TotalTries = ???
		// Update HUD Level
	}
	if (room == "FOR")
	{
		GetTime(RoomThree.SolvedPuzzle);
		RoomThree.TotalTries = CauldronHeated;
		// Update HUD Level
	}
}


void UMetrics::GetIncrement(UPARAM(ref) int32 &var)
{
	var++;
}


void UMetrics::CreateJSON(int32 id, FDateTime date, FRoom roomOne, FRoom roomTwo, FRoom roomThree, FTimespan startGame, FTimespan endGame, TArray<FPlayerPath> path)
{
	//TODO create json object
	//TODO Call Printer
	return;
}


void UMetrics::FileWriter(FString JSONObject)
{
	//TODO Print to file
	return;
}
