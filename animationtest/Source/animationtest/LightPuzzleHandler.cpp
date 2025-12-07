#include "LightPuzzleHandler.h"
#include "Engine/World.h"

ALightPuzzleHandler::ALightPuzzleHandler()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ALightPuzzleHandler::BeginPlay()
{
    Super::BeginPlay();




    FVector Origin = GetActorLocation();
    float HalfWidth = (GridWidth - 1) * CellSize * 0.5f;
    float HalfHeight = (GridHeight - 1) * CellSize * 0.5f;


    TileGrid.SetNum(GridWidth);
    for (int32 X = 0; X < GridWidth; ++X)
    {
        TileGrid[X].SetNum(GridHeight);

        for (int32 Y = 0; Y < GridHeight; ++Y)
        {
            FVector SpawnLoc = Origin + FVector(X * CellSize - HalfWidth, Y * CellSize - HalfHeight, ZOffset);
            ALightPiece* Tile = GetWorld()->SpawnActor<ALightPiece>(ActorToSpawn, SpawnLoc, FRotator::ZeroRotator);

            if (Tile)
            {
                Tile->GridX = X;
                Tile->GridY = Y;
                Tile->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);


                Tile->OnTileInteracted.AddDynamic(this, &ALightPuzzleHandler::OnTileInteracted);


                TileGrid[X][Y] = Tile;
            }
        }
    }


}

void ALightPuzzleHandler::OnTileInteracted(ALightPiece* Tile)
{
    if (!Tile) return;
    if (Completed) return;

    int32 X = Tile->GridX;
    int32 Y = Tile->GridY;


    ToggleTileAt(X, Y);
    ToggleTileAt(X + 1, Y);
    ToggleTileAt(X - 1, Y);
    ToggleTileAt(X, Y + 1);
    ToggleTileAt(X, Y - 1);
    CheckComplete();
}

void ALightPuzzleHandler::ToggleTileAt(int32 X, int32 Y)
{
    if (X < 0 || X >= GridWidth || Y < 0 || Y >= GridHeight)
        return;

    ALightPiece* Tile = TileGrid[X][Y];
    if (Tile)
    {
        Tile->ToggleLight();
    }
}

void ALightPuzzleHandler::BroadcastCompletion()
{
    OnCompleted.Broadcast(this);
}

void ALightPuzzleHandler::CheckComplete()
{
    Completed = true;

    for (int32 X = 0; X < GridWidth; ++X)
    {
        for (int32 Y = 0; Y < GridHeight; ++Y)
        {
            ALightPiece* Tile = TileGrid[X][Y];
            if (Tile && !Tile->Lit)
            {
                Completed = false;
                return;
            }
        }
    }

    BroadcastCompletion();

}