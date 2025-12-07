#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightPiece.h"
#include "LightPuzzleHandler.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCompleted, ALightPuzzleHandler*, Handler);

UCLASS()
class ANIMATIONTEST_API ALightPuzzleHandler : public AActor
{
    GENERATED_BODY()

public:
    ALightPuzzleHandler();

protected:
    virtual void BeginPlay() override;

    void CheckComplete();

public:
    UPROPERTY(EditAnywhere, Category = "Grid Settings")
    TSubclassOf<ALightPiece> ActorToSpawn;

    UPROPERTY(EditAnywhere, Category = "Grid Settings")
    int32 GridWidth = 5;

    UPROPERTY(EditAnywhere, Category = "Grid Settings")
    int32 GridHeight = 5;

    UPROPERTY(EditAnywhere, Category = "Grid Settings")
    float CellSize = 200.0f;

    UPROPERTY(EditAnywhere, Category = "Grid Settings")
    float ZOffset = 0.0f;

    UFUNCTION(BluePrintImplementableEvent)
    void DestroyDoor();

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnCompleted OnCompleted;

    UFUNCTION(BlueprintCallable)
    void BroadcastCompletion();


    TArray<TArray<ALightPiece*>> TileGrid;


    UFUNCTION()
    void OnTileInteracted(ALightPiece* Tile);

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Puzzle State")
    bool Completed = false;


private:
    void ToggleTileAt(int32 X, int32 Y);


};
