// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "Components/ActorComponent.h"
#include "RoomOneDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorOneEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SENIOR_API URoomOneDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URoomOneDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable, Category="IFDoor")
		FDoorOneEvent OnOpen;

	UPROPERTY(BlueprintAssignable, Category="IFDoor")
		FDoorOneEvent OnClose;

private:
	UPROPERTY(EditAnywhere)
		ATriggerVolume* BadApples = nullptr;
	
	UPROPERTY(EditAnywhere)
		ATriggerVolume* GoodApples = nullptr;

	// Returns the response for the players solution
	bool CheckSolution();

	const int GoodAppleWeight = 8;

	const int BadAppleWeight = 9;

};
