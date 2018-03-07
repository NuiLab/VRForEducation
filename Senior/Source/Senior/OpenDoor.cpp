// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();

	if (!IFTriggerVolume)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing IF STATEMENT Trigger Volume."), *GetOwner()->GetName());
	}
	
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (AllPlatesPressed())
	{
		OnOpen.Broadcast();
		//UE_LOG(LogTemp, Error, TEXT("OPEN!"));
	}
	else
	{
		OnClose.Broadcast();
		//UE_LOG(LogTemp, Error, TEXT("CLOSE"));
	}
	// ...
}

bool UOpenDoor::AllPlatesPressed()
{
	return (GetTotalActorsOnPlate() > TotalApples);
}

float UOpenDoor::GetTotalActorsOnPlate()
{
	float TotalActors = 0.f;

	// Find all the overlapping authors
	TArray<AActor*> ActorsArray;
	if (!IFTriggerVolume) { return TotalActors; }
	IFTriggerVolume->GetOverlappingActors(OUT ActorsArray);

	TotalActors = ActorsArray.Num();

	return TotalActors;
}

