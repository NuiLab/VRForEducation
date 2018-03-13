// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "ARRBotLight.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBLightEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SENIOR_API UARRBotLight : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UARRBotLight();

	UPROPERTY(BlueprintAssignable)
		FBLightEvent OnValid;

	UPROPERTY(BlueprintAssignable)
		FBLightEvent OnInvalid;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* ARRTriggerVolume4 = nullptr;

	UPROPERTY(EditAnywhere)
		FString BookIndex4 = "Book_23";

	UPROPERTY(EditAnywhere)
		ATriggerVolume* ARRTriggerVolume5 = nullptr;

	UPROPERTY(EditAnywhere)
		FString BookIndex5 = "Book_26";

	// The owning door
	AActor* Owner = nullptr;

	//Returns total Ammount of Actors
	bool CorrectOrder();
	
};
