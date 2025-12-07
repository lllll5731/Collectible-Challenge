// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectibleComponent_Emotes.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"


// Sets default values for this component's properties
UCollectibleComponent_Emotes::UCollectibleComponent_Emotes()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}



void UCollectibleComponent_Emotes::CollectAndDestroy(AActor* OtherActor, AActor* Owner) {

	if (!OtherActor) return;

	
	FProperty* Prop = OtherActor->GetClass()->FindPropertyByName(TEXT("Collectibles"));

	if (Prop)
	{
		
		if (FIntProperty* IntProp = CastField<FIntProperty>(Prop))
		{
			int32 CollectiblesValue = IntProp->GetPropertyValue_InContainer(OtherActor);

			
			CollectiblesValue++;

			
			IntProp->SetPropertyValue_InContainer(OtherActor, CollectiblesValue);

			UE_LOG(LogTemp, Log, TEXT("New Collectibles Value: %d"), CollectiblesValue);
		}
	}

	OnCollected.Broadcast();
	
	Owner->Destroy();
}


// Called when the game starts
void UCollectibleComponent_Emotes::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	UBoxComponent* BoxComponent = Cast<UBoxComponent>(GetOwner()->GetComponentByClass(UBoxComponent::StaticClass()));
	if (BoxComponent)
	{
		BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &UCollectibleComponent_Emotes::OnOverlapBegin);

	}




	//AActor* OwnerActor = GetOwner();
	//if (OwnerActor)
	//{
	//	OwnerActor->Destroy();
	//}

	
}


void UCollectibleComponent_Emotes::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->ActorHasTag("Player"))
	{
		AActor* OwnerActor = GetOwner();

		CollectAndDestroy(OtherActor, OwnerActor);
	}
}

// Called every frame
void UCollectibleComponent_Emotes::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	if (AActor* Owner = GetOwner())
	{
		
		FRotator CurrentRot = Owner->GetActorRotation();
		CurrentRot.Yaw += RotSpeed * DeltaTime;
		Owner->SetActorRotation(CurrentRot);
	}
}



