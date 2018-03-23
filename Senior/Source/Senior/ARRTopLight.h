// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "ARRTopLight.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTLightEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SENIOR_API UARRTopLight : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UARRTopLight();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable)
		FTLightEvent OnValid;

	UPROPERTY(BlueprintAssignable)
		FTLightEvent OnInvalid;

private:

	UPROPERTY(EditAnywhere)
		ATriggerVolume* ARRTriggerVolume0 = nullptr;

	UPROPERTY(EditAnywhere)
		FString BookIndex0 = "Book_1";

	UPROPERTY(EditAnywhere)
		ATriggerVolume* ARRTriggerVolume1 = nullptr;

	UPROPERTY(EditAnywhere)
		FString BookIndex1 = "Book_2";

	// The owning door
	AActor* Owner = nullptr;

	//Returns total Ammount of Actors
	bool CorrectOrder();
	
};
