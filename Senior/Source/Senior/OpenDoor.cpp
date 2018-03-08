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

	if (!ARRTriggerVolume0)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing Trigger Volume for Index 0!"), *GetOwner()->GetName());
	}

	if (!ARRTriggerVolume1)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing Trigger Volume for Index 1!"), *GetOwner()->GetName());
	}

	if (!ARRTriggerVolume2)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing Trigger Volume for Index 2!"), *GetOwner()->GetName());
	}

	if (!ARRTriggerVolume3)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing Trigger Volume for Index 3!"), *GetOwner()->GetName());
	}

	if (!ARRTriggerVolume4)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing Trigger Volume for Index 4!"), *GetOwner()->GetName());
	}

	if (!ARRTriggerVolume5)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing Trigger Volume for Index 5!"), *GetOwner()->GetName());
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
	return CorrectBookSequence;
}

float UOpenDoor::GetTotalActorsOnPlate()
{
	float TotalActors = 0.f;

	// Find all the overlapping authors
	TArray<AActor*> ActorsArray;
	if (!ARRTriggerVolume0) { return TotalActors; }
	ARRTriggerVolume0->GetOverlappingActors(OUT ActorsArray);

	TotalActors = ActorsArray.Num();

	return TotalActors;
}

