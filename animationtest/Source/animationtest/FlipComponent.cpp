// Fill out your copyright notice in the Description page of Project Settings.

#include "FlipComponent.h"
#include "Components/BoxComponent.h"


// Sets default values for this component's properties
UFlipComponent::UFlipComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFlipComponent::BeginPlay()
{
	Super::BeginPlay();

	UBoxComponent* BoxComponent = Cast<UBoxComponent>(GetOwner()->GetComponentByClass(UBoxComponent::StaticClass()));
	if (BoxComponent)
	{
		BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &UFlipComponent::OnOverlapBegin);

	}
}
void UFlipComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->ActorHasTag("Player"))
	{
		FlipPlatform();
	}
}


void UFlipComponent::FlipPlatform()
{
	if (bFlipping)
		return;

	bFlipping = true;
	FlipElapsedTime = 0.0f;
	UStaticMeshComponent* StaticMeshComponent = Cast<UStaticMeshComponent>(GetOwner()->GetComponentByClass(UStaticMeshComponent::StaticClass()));
	StartRotation = StaticMeshComponent->GetRelativeRotation();
	TargetRotation = StartRotation + FRotator(180.f, 0.f, 0.f);
}


// Called every frame
void UFlipComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bFlipping)
	{
		FlipElapsedTime += DeltaTime;
		float Alpha = FMath::Clamp(FlipElapsedTime / FlipDuration, 0.f, 1.f);
		UStaticMeshComponent* StaticMeshComponent = Cast<UStaticMeshComponent>(GetOwner()->GetComponentByClass(UStaticMeshComponent::StaticClass()));
		FRotator NewRotation = FMath::Lerp(StartRotation, TargetRotation, Alpha);
		StaticMeshComponent->SetRelativeRotation(NewRotation);

		if (Alpha >= 1.f)
		{
			bFlipping = false;
		}
	}

	// ...
}

