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
	Player = GetOwner();
	// ..
	StartGame();
	FTimerHandle handle;
	GetWorld()->GetTimerManager().SetTimer(handle, this, &UMetrics::GetPlayerPath, 1.0f, true, 0.0f);
	//EndGame();
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
	FString MetricsString;

	MetricsString.AppendInt(PlayerID);
	MetricsString.AppendChar(',');
	MetricsString.Append(*Date.ToString().LeftChop(9));
	MetricsString.AppendChar(',');
	//Room One Metrics
	MetricsString.Append(*RoomOne.EnterRoom.ToString());
	MetricsString.AppendChar(',');
	MetricsString.Append(*RoomOne.StartPuzzle.ToString());
	MetricsString.AppendChar(',');
	MetricsString.Append(*RoomOne.SolvedPuzzle.ToString());
	MetricsString.AppendChar(',');
	MetricsString.Append(*RoomOne.ExitRoom.ToString());
	MetricsString.AppendChar(',');
	MetricsString.AppendInt(RoomOne.TotalTries);
	MetricsString.AppendChar(',');
	//Room Two Metrics
	MetricsString.Append(*RoomTwo.EnterRoom.ToString());
	MetricsString.AppendChar(',');
	MetricsString.Append(*RoomTwo.StartPuzzle.ToString());
	MetricsString.AppendChar(',');
	MetricsString.Append(*RoomTwo.SolvedPuzzle.ToString());
	MetricsString.AppendChar(',');
	MetricsString.Append(*RoomTwo.ExitRoom.ToString());
	MetricsString.AppendChar(',');
	MetricsString.AppendInt(RoomTwo.TotalTries);
	MetricsString.AppendChar(',');
	//Room Three Metrics
	MetricsString.Append(*RoomThree.EnterRoom.ToString());
	MetricsString.AppendChar(',');
	MetricsString.Append(*RoomThree.StartPuzzle.ToString());
	MetricsString.AppendChar(',');
	MetricsString.Append(*RoomThree.SolvedPuzzle.ToString());
	MetricsString.AppendChar(',');
	MetricsString.Append(*RoomThree.ExitRoom.ToString());
	MetricsString.AppendChar(',');
	MetricsString.AppendInt(RoomThree.TotalTries);
	//Start and EndTime
	MetricsString.AppendChar(',');
	MetricsString.Append(*StartTime.ToString());
	MetricsString.AppendChar(',');
	MetricsString.Append(*EndTime.ToString());

	FileWriter(MetricsString, false);
	
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


void UMetrics::GetPlayerPath()
{
	PlayerPath.PlayerLocation = Player->GetActorLocation();
	PlayerPath.PlayerRotation = Player->GetActorRotation();
	PathArray.Add(PlayerPath);

	//UE_LOG(LogTemp, Warning, TEXT("Location: %s\n"), *PlayerPath.PlayerLocation.ToString());
	//UE_LOG(LogTemp, Warning, TEXT("Rotation: %s\n"), *PlayerPath.PlayerRotation.ToString());
}


void UMetrics::CreateJSON(int32 id, FDateTime date, FRoom roomOne, FRoom roomTwo, FRoom roomThree, FTimespan startGame, FTimespan endGame, TArray<FPlayerPath> path)
{
	//TODO create json object
	//TODO Call Printer
	return;
}


void UMetrics::FileWriter(FString JSONObject, bool isJSON)
{
	//FString SaveDirectory = FString("X:/WorkSpace/Unreal/Projects/VREducation/Senior/Content/TempFiles");
	FString SaveDirectory = FString("C:/Users/Danny/Documents/Unreal Projects/VRForEducation/VRForEducation/Senior/Content/TempFiles");
	FString FileName;
	FString TextToSave;
	TextToSave += *JSONObject;
	TextToSave.AppendChar('\r');
	TextToSave.AppendChar('\n');

	if (isJSON)
	{
		FileName = FString("Metrics.json");
	}
	else
	{
		FileName = FString("Metrics.txt");
	}
	bool AllowOverwriting = true;

	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	//// CreateDirectoryTree returns true if the destination
	//// directory existed prior to call or has been created
	//// during the call.
	if (PlatformFile.CreateDirectoryTree(*SaveDirectory))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Ready to Print to file: %s"), *JSONObject);
		//UE_LOG(LogTemp, Warning, TEXT(">>> %s"), *TextToSave);
		// Get absolute file path
		FString AbsoluteFilePath = SaveDirectory + "/" + FileName;

		UE_LOG(LogTemp, Warning, TEXT("Path: %s"), *AbsoluteFilePath);
		// Allow overwriting or file doesn't already exist
		if (AllowOverwriting || !PlatformFile.FileExists(*AbsoluteFilePath))
		{
			//FFileHelper::SaveStringToFile(TextToSave, *AbsoluteFilePath);
			FFileHelper::SaveStringToFile(TextToSave, *AbsoluteFilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Append);
		}
	}
	return;
}
