// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CollectibleComponent_Emotes.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCollected);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ANIMATIONTEST_API UCollectibleComponent_Emotes : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCollectibleComponent_Emotes();


	UPROPERTY(BlueprintAssignable, Category = "Collectible")
	FOnCollected OnCollected;
	


	void CollectAndDestroy(AActor * OtherActor, AActor * Owner);

	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:

	float RotSpeed = 10.f;
	FRotator StartRotation;
	FRotator TargetRotation;

		
};
