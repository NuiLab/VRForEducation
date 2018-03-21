// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "Metrics.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SENIOR_API UMetrics : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMetrics();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	UPROPERTY(EditAnywhere)
		ATriggerVolume* ARRMetrics = nullptr;

	// The owning door
	AActor* Owner = nullptr;
	
};
