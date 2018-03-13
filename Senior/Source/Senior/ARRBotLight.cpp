// Fill out your copyright notice in the Description page of Project Settings.

#include "ARRBotLight.h"


// Sets default values for this component's properties
UARRBotLight::UARRBotLight()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UARRBotLight::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();

	if (!ARRTriggerVolume4)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing Trigger Volume for Index 4!"), *GetOwner()->GetName());
	}

	if (!ARRTriggerVolume5)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing Trigger Volume for Index 5!"), *GetOwner()->GetName());
	}
	// ...
	
}


// Called every frame
void UARRBotLight::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
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

bool UARRBotLight::CorrectOrder()
{
	bool Book4 = false;
	bool Book5= false;


	//UE_LOG(LogTemp, Error, TEXT("COrrect Book Sequence Called"));

	// Find all the overlapping authors
	TArray<AActor*> BookArray;
	if (!ARRTriggerVolume4) { return false; }
	if (!ARRTriggerVolume5) { return false; }


	//UE_LOG(LogTemp, Error, TEXT("All Plates exist"));

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

	return Book4 && Book5;
}

