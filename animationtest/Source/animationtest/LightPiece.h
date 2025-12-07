#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightPiece.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTileInteracted, ALightPiece*, Tile);

UCLASS()
class ANIMATIONTEST_API ALightPiece : public AActor
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
    int32 GridX;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
    int32 GridY;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnTileInteracted OnTileInteracted;

    UFUNCTION(BlueprintCallable)
    void TriggerInteraction();

    UFUNCTION(BlueprintImplementableEvent)
    void ToggleLight();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle State")
    bool Lit = false;

};
