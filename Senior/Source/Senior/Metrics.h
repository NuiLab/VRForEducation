// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Core/Public/GenericPlatform/GenericPlatformFile.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Core/Public/HAL/PlatformFilemanager.h"
#include "Runtime/Core/Public/Misc/FileHelper.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Runtime/Core/Public/Misc/DateTime.h"
#include "Runtime/Core/Public/Misc/Paths.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "Metrics.generated.h"


USTRUCT()
struct FRoom {
	GENERATED_USTRUCT_BODY()

	FTimespan EnterRoom;
	FTimespan StartPuzzle;
	FTimespan SolvedPuzzle;
	FTimespan ExitRoom;
	int32 TotalTries;
};


USTRUCT()
struct FPlayerPath {
	GENERATED_USTRUCT_BODY()
	
	FVector PlayerLocation;
	FRotator PlayerRotation;
	
	FString ToString()
	{
		FString x = FString::SanitizeFloat(PlayerLocation.X);
		FString y = FString::SanitizeFloat(PlayerLocation.Y);
		FString z = FString::SanitizeFloat(PlayerLocation.Z);
		FString pitch = FString::SanitizeFloat(PlayerRotation.Pitch);
		FString yaw = FString::SanitizeFloat(PlayerRotation.Yaw);
		FString roll = FString::SanitizeFloat(PlayerRotation.Roll);
				
		FString ToStringReturn;
		ToStringReturn = "{\"location\" : \"" + x + ',' + y + ',' + z + "\", \"rotation\" : \"" + pitch + "," + yaw + "," + roll + "\"}";

		return  ToStringReturn;
	}
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
		void PuzzleStarted(FString room);

	UFUNCTION(BlueprintCallable, Category = "Game Event")
		void PuzzleSolved(FString room);

	UFUNCTION(BlueprintCallable, Category = "Game Event")
		void GetIncrement(UPARAM(ref) int32 &var);

	UFUNCTION()
		void GetPlayerPath();

	void GetDate(FDateTime &current);

	void GetTime(FTimespan &current);

	void FileWriter(FString JSONObject, FString file, bool isJSON);

	// Metrics
	/** Number of times the Scale was used. */
	UPROPERTY(BlueprintReadWrite, Category = "Metric")
		int32 ScaleUsed = 0;

	/** Number of times the Cauldron was heated. */
	UPROPERTY(BlueprintReadWrite, Category = "Metric")
		int32 CauldronHeated = 0;

private:
	// Metrics
	const int32 PlayerID = 10;
	FDateTime Date;
	FTimespan StartTime;
	FTimespan EndTime;
	FRoom RoomOne;
	FRoom RoomTwo;
	FRoom RoomThree;
	FTimerHandle Handle;
	FPlayerPath PlayerPath;
	TArray<FPlayerPath> PathArray;

	// The Player
	AActor* Player = nullptr;
};