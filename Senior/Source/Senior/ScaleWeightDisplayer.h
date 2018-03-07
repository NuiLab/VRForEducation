// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerBox.h"
#include "ScaleWeightDisplayer.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SENIOR_API UScaleWeightDisplayer : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UScaleWeightDisplayer();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ActivateScale();

	void GetWeight(int left, int right);

	void DisplayWeight(int left, int right);

private:
	UPROPERTY(EditAnywhere)
		ATriggerBox* ScaleLeftSide = nullptr;

	UPROPERTY(EditAnywhere)
		ATriggerBox* ScaleRightSide = nullptr;

	//Keep track of left side weigth
	int left;

	//Keep track of right side weigth
	int right;

	//Count the ammount of apples placed on the weight
	int counter = 0;
		
};
