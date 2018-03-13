// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SENIOR_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable)
		FDoorEvent OnOpen;

	UPROPERTY(BlueprintAssignable)
		FDoorEvent OnClose;

private:

	UPROPERTY(EditAnywhere)
		ATriggerVolume* ARRTriggerVolume0 = nullptr;

	UPROPERTY(EditAnywhere)
		FString BookIndex0 = "Book_8";

	UPROPERTY(EditAnywhere)
		ATriggerVolume* ARRTriggerVolume1 = nullptr;

	UPROPERTY(EditAnywhere)
		FString BookIndex1 = "Book_14";

	UPROPERTY(EditAnywhere)
		ATriggerVolume* ARRTriggerVolume2 = nullptr;

	UPROPERTY(EditAnywhere)
		FString BookIndex2 = "Book_17";

	UPROPERTY(EditAnywhere)
		ATriggerVolume* ARRTriggerVolume3 = nullptr;

	UPROPERTY(EditAnywhere)
		FString BookIndex3 = "Book_20";

	UPROPERTY(EditAnywhere)
		ATriggerVolume* ARRTriggerVolume4 = nullptr;

	UPROPERTY(EditAnywhere)
		FString BookIndex4 = "Book_23";

	UPROPERTY(EditAnywhere)
		ATriggerVolume* ARRTriggerVolume5 = nullptr;

	UPROPERTY(EditAnywhere)
		FString BookIndex5 = "Book_26";

	UPROPERTY(EditAnywhere)
		class ULightComponent* ARR_TopLight = nullptr;

	//UPROPERTY(EditAnywhere)
		//bool CorrectBookSequence = false;

	// The owning door
	AActor* Owner = nullptr;

	//Returns total Ammount of Actors
	bool CorrectBookSequence();

	//Returns If all plates are activated
	bool AllPlatesPressed();
	
};
