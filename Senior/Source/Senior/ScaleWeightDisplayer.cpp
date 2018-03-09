// Fill out your copyright notice in the Description page of Project Settings.

#include "ScaleWeightDisplayer.h"


// Sets default values for this component's properties
UScaleWeightDisplayer::UScaleWeightDisplayer()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UScaleWeightDisplayer::BeginPlay()
{
	Super::BeginPlay();
	
	// ...
	
}


// Called every frame
void UScaleWeightDisplayer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//ActivateScale();
		
	int32 height = 10;

		//GoUp.Broadcast(height);

		//GoDown.Broadcast(height*2);
	// ...
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
	//if (!ActorsLeftSide) { return TotalMass; }
	ScaleLeftSide->GetOverlappingActors(OUT ActorsLeftSide);

	for (auto* Actor : ActorsLeftSide)
	{
		left += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	TArray<AActor*> ActorsRightSide;
	//if (!ActorsRightSide) { return TotalMass; }
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
		UE_LOG(LogTemp, Warning, TEXT("Tilted LEFT, Left: %d, Right: %d"), left, right);
	}
	else if (left < right)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tilted RIGHT, Left: %d, Right: %d"), left, right);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Balanced, Left: %d, Right: %d"), left, right);
	}
}
