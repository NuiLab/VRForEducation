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

	Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	StartGame();
	GetWorld()->GetTimerManager().SetTimer(Handle, this, &UMetrics::GetPlayerPath, 1.0f, true, 0.0f);
	//PlayerID = Date.ToUnixTimestamp();
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
	FString JSONString;
	FString PathString;
	int32 index;
	int32 length = PathArray.Num();

	// Metrics
	MetricsString.AppendInt(PlayerID);
	MetricsString.Append("," + Date.ToString().LeftChop(9));
	// Room One Metrics
	MetricsString.Append("," + RoomOne.EnterRoom.ToString() + ",");
	MetricsString.Append(RoomOne.StartPuzzle.ToString() + ",");
	MetricsString.Append(RoomOne.SolvedPuzzle.ToString() + ",");
	MetricsString.Append(RoomOne.ExitRoom.ToString() + ",");
	MetricsString.AppendInt(RoomOne.TotalTries);
	// Room Two Metrics
	MetricsString.Append("," + RoomTwo.EnterRoom.ToString() + ",");
	MetricsString.Append(RoomTwo.StartPuzzle.ToString() + ",");
	MetricsString.Append(RoomTwo.SolvedPuzzle.ToString() + ",");
	MetricsString.Append(RoomTwo.ExitRoom.ToString() + ",");
	MetricsString.AppendInt(RoomTwo.TotalTries);
	// Room Three Metrics
	MetricsString.Append("," + RoomThree.EnterRoom.ToString() + ",");
	MetricsString.Append(RoomThree.StartPuzzle.ToString() + ",");
	MetricsString.Append(RoomThree.SolvedPuzzle.ToString() + ",");
	MetricsString.Append(RoomThree.ExitRoom.ToString() + ",");
	MetricsString.AppendInt(RoomThree.TotalTries);
	// Start and EndTime
	MetricsString.Append("," + StartTime.ToString() + ",");
	MetricsString.Append(EndTime.ToString());

	FileWriter(MetricsString, "Metrics", false);

	// Path
	PathString.Append("[");
	for (index = 0; index < length-1; index++)
	{
		PathString.Append(PathArray[index].ToString() + ",");
	}
	PathString.Append(PathArray[index].ToString() + "]");

	JSONString = "{\r\n\t\"id\" : \"" + FString::FromInt(PlayerID) + "\", \r\n\t\"date\" : \"" + Date.ToString().LeftChop(9) + "\",\r\n\t\"roomOne\" : {\"enterRoom\": \"" + RoomOne.EnterRoom.ToString() + "\", \"startPuzzle\" : \"" + RoomOne.StartPuzzle.ToString() + "\", \"endPuzzle\" : \"" + RoomOne.SolvedPuzzle.ToString() + "\", \"endRoom\" : \"" + RoomOne.ExitRoom.ToString() + "\", \"PuzzleTries\" : \"" + FString::FromInt(RoomOne.TotalTries) + "\" },\r\n\t\"roomTwo\" : {\"enterRoom\": \"" + RoomTwo.EnterRoom.ToString() + "\", \"startPuzzle\" : \"" + RoomTwo.StartPuzzle.ToString() + "\", \"endPuzzle\" : \"" + RoomTwo.SolvedPuzzle.ToString() + "\", \"endRoom\" : \"" + RoomTwo.ExitRoom.ToString() + "\", \"PuzzleTries\" : \"" + FString::FromInt(RoomTwo.TotalTries) + "\"},\r\n\t\"roomThree\" : {\"enterRoom\": \"" + RoomThree.EnterRoom.ToString() + "\", \"startPuzzle\" : \"" + RoomThree.StartPuzzle.ToString() + "\", \"endPuzzle\" : \"" + RoomThree.SolvedPuzzle.ToString() + "\", \"endRoom\" : \"" + RoomThree.ExitRoom.ToString() + "\", \"PuzzleTries\" : \"" + FString::FromInt(RoomThree.TotalTries) + "\"},\r\n\t\"gameTimes\" : {\"startGame\":\"" + StartTime.ToString() + "\", \"endGame\" : \"" + EndTime.ToString() + "\"},\r\n\t\"path\" : " + PathString + "\r\n},";
	
	FileWriter(JSONString, "Metrics", true);
	
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
	}
	if (room == "ARR")
	{
		GetTime(RoomOne.ExitRoom);
		GetTime(RoomTwo.EnterRoom);
	}
	if (room == "FOR")
	{
		GetTime(RoomTwo.ExitRoom);
		GetTime(RoomThree.EnterRoom);
	}
	if (room == "Prize")
	{
		GetTime(RoomThree.ExitRoom);
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
	GetTime(Current);
	PlayerPath.Time = Current;
	PlayerPath.PlayerLocation = Player->GetActorLocation();
	PlayerPath.PlayerRotation = Player->GetActorRotation();
	PathArray.Add(PlayerPath);
	/*
	FString temp;
	temp.Append(PlayerPath.ToString());
	UE_LOG(LogTemp, Warning, TEXT("PlayerPath: %s\n"), *temp);
	*/
}


void UMetrics::FileWriter(FString JSONObject, FString file, bool isJSON)
{
	FString FilePath;
	FString SaveDirectory;
	FString TextToSave;
	FString FileName;

	FilePath = FPaths::GameContentDir();
	SaveDirectory = FilePath + "TempFiles";
	TextToSave += *JSONObject;
	TextToSave.Append("\r\n");

	if (isJSON)
	{
		FileName = FString(file + ".json");
	}
	else
	{
		FileName = FString(file + ".txt");
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

		//UE_LOG(LogTemp, Warning, TEXT("Path: %s"), *AbsoluteFilePath);
		// Allow overwriting or file doesn't already exist
		if (AllowOverwriting || !PlatformFile.FileExists(*AbsoluteFilePath))
		{
			//FFileHelper::SaveStringToFile(TextToSave, *AbsoluteFilePath);
			FFileHelper::SaveStringToFile(TextToSave, *AbsoluteFilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Append);
		}
	}
	return;
}
