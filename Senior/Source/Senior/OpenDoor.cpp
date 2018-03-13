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
	return CorrectBookSequence();
}

bool UOpenDoor::CorrectBookSequence()
{
	bool Book0 = false;
	bool Book1 = false;
	bool Book2 = false;
	bool Book3 = false;
	bool Book4 = false;
	bool Book5 = false;

	//UE_LOG(LogTemp, Error, TEXT("COrrect Book Sequence Called"));

	// Find all the overlapping authors
	TArray<AActor*> BookArray;
	if (!ARRTriggerVolume0) { return false; }
	if (!ARRTriggerVolume1) { return false; }
	if (!ARRTriggerVolume2) { return false; }
	if (!ARRTriggerVolume3) { return false; }
	if (!ARRTriggerVolume4) { return false; }
	if (!ARRTriggerVolume5) { return false; }
	
	//UE_LOG(LogTemp, Error, TEXT("All Plates exist"));

	ARRTriggerVolume0->GetOverlappingActors(OUT BookArray);
	if (BookArray.Num() == 1)
	{
		if (*BookArray[0]->GetName() == BookIndex0)
		{
			Book0 = true;
		}
	}

	ARRTriggerVolume1->GetOverlappingActors(OUT BookArray);
	if (BookArray.Num() == 1)
	{
		if (*BookArray[0]->GetName() == BookIndex1)
		{
			Book1 = true;
		}
	}

	ARRTriggerVolume2->GetOverlappingActors(OUT BookArray);
	if (BookArray.Num() == 1)
	{
		if (*BookArray[0]->GetName() == BookIndex2)
		{
			Book2 = true;
		}
	}

	ARRTriggerVolume3->GetOverlappingActors(OUT BookArray);
	if (BookArray.Num() == 1)
	{
		if (*BookArray[0]->GetName() == BookIndex3)
		{
			Book3 = true;
		}
	}

	ARRTriggerVolume4->GetOverlappingActors(OUT BookArray);
	if (BookArray.Num() == 1)
	{
		if (*BookArray[0]->GetName() == BookIndex4)
		{
			Book4 = true;
		}
	}

	ARRTriggerVolume5->GetOverlappingActors(OUT BookArray);
	if (BookArray.Num() == 1)
	{
		if (*BookArray[0]->GetName() == BookIndex5)
		{
			Book5 = true;
		}
	}
	
	return Book0 && Book1 && Book2 & Book3 && Book4 && Book5;
}

