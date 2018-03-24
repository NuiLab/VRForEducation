// Fill out your copyright notice in the Description page of Project Settings.

#include "ScaleWeightDisplayer.h"


// Sets default values for this component's properties
UScaleWeightDisplayer::UScaleWeightDisplayer()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UScaleWeightDisplayer::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UScaleWeightDisplayer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


// Called when the user presses a button
void UScaleWeightDisplayer::ActivateScale()
{
	left = 0;
	right = 0;
	GetWeight(left, right);
}


void UScaleWeightDisplayer::GetWeight(int left, int right)
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


void UScaleWeightDisplayer::DisplayWeight(int left, int right)
{
	if (left > right)
	{
		FVector heightL = { 0.0f, 0.0f, -15.0f };
		FVector heightR = { 0.0f, 0.0f, 15.0f };
		FRotator tiltDeg = { 15.0f, 0.0f, 0.0f };
		MagicScale.Broadcast(heightL, heightR, tiltDeg);
		//UE_LOG(LogTemp, Warning, TEXT("Tilted LEFT, Left: %d, Right: %d"), left, right);
	}
	else if (left < right)
	{
		FVector heightL = { 0.0f, 0.0f, 15.0f };
		FVector heightR = { 0.0f, 0.0f, -15.0f };
		FRotator tiltDeg = { -15.0f, 0.0f, 0.0f };
		MagicScale.Broadcast(heightL, heightR, tiltDeg);
		//UE_LOG(LogTemp, Warning, TEXT("Tilted RIGHT, Left: %d, Right: %d"), left, right);
	}
	else
	{
		FVector heightL = { 0.0f, 0.0f, 0.0f };
		FVector heightR = { 0.0f, 0.0f, 0.0f };
		FRotator tiltDeg = { 0.0f, 0.0f, 0.0f };
		MagicScale.Broadcast(heightL, heightR, tiltDeg);
		//UE_LOG(LogTemp, Warning, TEXT("Balanced, Left: %d, Right: %d"), left, right);
	}
}