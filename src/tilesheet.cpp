#include "tilesheet.h"

Texture2D getTileTexture(Vector2 src) {
    // Get the tiilesheet path
    static Image tilesheetImage = LoadImage("assets/Tilesheet/tilesheet_complete.png");
    
    // Get the specific tile
    Rectangle cropRect = { (float)(src.x * 64), (float)(src.y * 64), 64.f, 64.f };

    // Make a image of the tile
    Image tileImage = ImageFromImage(tilesheetImage, cropRect);
    
    // Make a texture of the tile
    Texture2D tileTexture = LoadTextureFromImage(tileImage);

    // Unload the image
    UnloadImage(tileImage);
    
    // Return the tile
    return tileTexture;
}