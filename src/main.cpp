#include "raylib.h"
#include "player.h"

int main() {
    // Create window
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Overcharge 2D");

    // Set FPS
    SetTargetFPS(60);

    // Create player
    Player* player = new Player{100.f, 100.f};

    // Main loop
    while (!WindowShouldClose()) {
        // Game logic
        player->Update();

        // Drawings
        BeginDrawing();

            ClearBackground(DARKGRAY);
            player->Draw();

        EndDrawing();
    }

    // Delete player
    delete player;

    // Close window
    CloseWindow();

    return 0;
}