// Fill out your copyright notice in the Description page of Project Settings.

#include "ARRMidLight.h"


// Sets default values for this component's properties
UARRMidLight::UARRMidLight()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UARRMidLight::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();

	if (!ARRTriggerVolume2)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing Trigger Volume for Index 2!"), *GetOwner()->GetName());
	}

	if (!ARRTriggerVolume3)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing Trigger Volume for Index 3!"), *GetOwner()->GetName());
	}
	// ...
	
}


// Called every frame
void UARRMidLight::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CorrectOrder())
	{
		OnValid.Broadcast();
		//UE_LOG(LogTemp, Error, TEXT("OPEN!"));
	}
	else
	{
		OnInvalid.Broadcast();
		//UE_LOG(LogTemp, Error, TEXT("CLOSE"));
	}

	// ...
}

bool UARRMidLight::CorrectOrder()
{
	bool Book2 = false;
	bool Book3 = false;


	//UE_LOG(LogTemp, Error, TEXT("COrrect Book Sequence Called"));

	// Find all the overlapping authors
	TArray<AActor*> BookArray;
	if (!ARRTriggerVolume2) { return false; }
	if (!ARRTriggerVolume3) { return false; }


	//UE_LOG(LogTemp, Error, TEXT("All Plates exist"));

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

	return Book2 && Book3;
}
