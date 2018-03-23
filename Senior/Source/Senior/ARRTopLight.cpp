// Fill out your copyright notice in the Description page of Project Settings.

#include "ARRTopLight.h"


// Sets default values for this component's properties
UARRTopLight::UARRTopLight()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UARRTopLight::BeginPlay()
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
	
}


// Called every frame
void UARRTopLight::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
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

bool UARRTopLight::CorrectOrder()
{
	bool Book0 = false;
	bool Book1 = false;


	//UE_LOG(LogTemp, Error, TEXT("COrrect Book Sequence Called"));

	// Find all the overlapping authors
	TArray<AActor*> BookArray;
	if (!ARRTriggerVolume0) { return false; }
	if (!ARRTriggerVolume1) { return false; }


	//UE_LOG(LogTemp, Error, TEXT("All Plates exist"));

	ARRTriggerVolume0->GetOverlappingActors(OUT BookArray);
	if (BookArray.Num() == 1)
	{
		//UE_LOG(LogTemp, Error, TEXT("Book %s"), *BookArray[0]->GetName());
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

	return Book0 && Book1;
}
