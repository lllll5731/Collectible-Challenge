#include "LightPiece.h"

void ALightPiece::TriggerInteraction()
{
    OnTileInteracted.Broadcast(this);
}
