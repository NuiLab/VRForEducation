// Fill out your copyright notice in the Description page of Project Settings.

#include "RoomOneDoor.h"


// Sets default values for this component's properties
URoomOneDoor::URoomOneDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void URoomOneDoor::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void URoomOneDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CheckSolution())
	{
		OnOpen.Broadcast();
	}
	else
	{
		OnClose.Broadcast();
	}
}


bool URoomOneDoor::CheckSolution()
{
	int left = 0;
	int right = 0;
	bool response = false;
	
	TArray<AActor*> ActorsLeftSide;
	BadApples->GetOverlappingActors(OUT ActorsLeftSide);

	for (auto* Actor : ActorsLeftSide)
	{
		left += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	TArray<AActor*> ActorsRightSide;
	GoodApples->GetOverlappingActors(OUT ActorsRightSide);

	for (auto* Actor : ActorsRightSide)
	{
		right += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	if (left == BadAppleWeight && right == GoodAppleWeight)
	{
		response = true;
	}
	
	return response;
}