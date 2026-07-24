#include "map.h"

#include "tilesheet.h"
#include "raymath.h"

Map::Map(int mapSize, Vector2 mapStart) {
    size = mapSize;
    pos = mapStart;
    
    // Filling map with ID 1 (brown tile)
    grid.resize(size, std::vector<int>(size, 1));

    brownTile = getTileTexture(Vector2{4.0f, 0.0f});
}

Map::~Map() {
    // Unloading texture
    UnloadTexture(brownTile);
}

void Map::Update() {}

void Map::Draw(Camera2D camera) {
    // Check the visibile map from the camera
    Vector2 topLeft = GetScreenToWorld2D({0, 0}, camera);
    Vector2 bottomRight = GetScreenToWorld2D({(float)GetScreenWidth(), (float)GetScreenHeight()}, camera);
    
    // Convert the cordinates in the world in tile indices
    int startX = Clamp((topLeft.x - pos.x) / 64.0f, 0, size);
    int startY = Clamp((topLeft.y - pos.y) / 64.0f, 0, size);
    int endX   = Clamp((bottomRight.x - pos.x) / 64.0f + 1, 0, size);
    int endY   = Clamp((bottomRight.y - pos.y) / 64.0f + 1, 0, size);

    // Draw only visibile tiles
    for (int i = startY; i < endY; i++) {
        for (int j = startX; j < endX; j++) {
            if (grid[i][j] == 1) {
                Vector2 tilePos = { pos.x + (j * 64.0f), pos.y + (i * 64.0f) };
                DrawTexture(brownTile, (int)tilePos.x, (int)tilePos.y, WHITE);
            }
        }
    }
}