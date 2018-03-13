// Fill out your copyright notice in the Description page of Project Settings.

#include "test.h"


// Sets default values
Atest::Atest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void Atest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Atest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called when the user presses a button
void Atest::ActivateScale()
{
	left = 0;
	right = 0;
	GetWeight(left, right);
}


void Atest::GetWeight(int left, int right)
{
	TArray<AActor*> ActorsLeftSide;
	ScaleLeftSide->GetOverlappingActors(OUT ActorsLeftSide);

	for (auto* Actor : ActorsLeftSide)
	{
		left += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	TArray<AActor*> ActorsRightSide;
	ScaleRightSide->GetOverlappingActors(OUT ActorsRightSide);

	for (auto* Actor : ActorsRightSide)
	{
		right += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	if (left == 0 && right == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Apples on Scale!"));
	}
	else
	{
		DisplayWeight(left, right);
		counter++;
	}
}


void Atest::DisplayWeight(int left, int right)
{
	if (left > right)
	{
		FVector heightL = { 0.0f, 0.0f, -15.0f };
		FVector heightR = { 0.0f, 0.0f, 15.0f };
		MagicScale.Broadcast(heightL, heightR);
		UE_LOG(LogTemp, Warning, TEXT("Tilted LEFT, Left: %d, Right: %d"), left, right);
	}
	else if (left < right)
	{
		FVector heightL = { 0.0f, 0.0f, 15.0f };
		FVector heightR = { 0.0f, 0.0f, -15.0f };
		MagicScale.Broadcast(heightL, heightR);
		UE_LOG(LogTemp, Warning, TEXT("Tilted RIGHT, Left: %d, Right: %d"), left, right);
	}
	else
	{
		FVector heightL = { 0.0f, 0.0f, 0.0f };
		FVector heightR = { 0.0f, 0.0f, 0.0f };
		MagicScale.Broadcast(heightL, heightR);
		UE_LOG(LogTemp, Warning, TEXT("Balanced, Left: %d, Right: %d"), left, right);
	}
}
