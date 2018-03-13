// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "ARRMidLight.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMLightEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SENIOR_API UARRMidLight : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UARRMidLight();

	UPROPERTY(BlueprintAssignable)
		FMLightEvent OnValid;

	UPROPERTY(BlueprintAssignable)
		FMLightEvent OnInvalid;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* ARRTriggerVolume2 = nullptr;

	UPROPERTY(EditAnywhere)
		FString BookIndex2 = "Book_17";

	UPROPERTY(EditAnywhere)
		ATriggerVolume* ARRTriggerVolume3 = nullptr;

	UPROPERTY(EditAnywhere)
		FString BookIndex3 = "Book_20";

	// The owning door
	AActor* Owner = nullptr;

	//Returns total Ammount of Actors
	bool CorrectOrder();
	
};
