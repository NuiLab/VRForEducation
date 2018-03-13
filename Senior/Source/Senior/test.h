// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/TriggerVolume.h"
#include "test.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FWeightEvent2, FVector, LeftHeight, FVector, RightHeight);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SENIOR_API Atest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Atest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintAssignable, Category = "Scale2")
		FWeightEvent2 MagicScale;

	UFUNCTION(BlueprintCallable, Category = "ScaleFunction2")
		void ActivateScale();

	void GetWeight(int left, int right);

	void DisplayWeight(int left, int right);

private:
	UPROPERTY(EditAnywhere)
		ATriggerVolume* ScaleLeftSide = nullptr;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* ScaleRightSide = nullptr;

	// Weight for left side of scale
	int left;

	// Weight for right side of scale
	int right;

	// Counter for the number of times the scale was activated
	int counter = 0;
	
};
