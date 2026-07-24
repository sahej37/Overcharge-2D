#include "raylib.h"
#include "player.h"
#include "map.h"

int main() {
    // Create window
    const int screenWidth = 1000;
    const int screenHeight = 550;
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Overcharge");

    // Set FPS
    SetTargetFPS(60);

    // Create map
    Map* map = new Map{40, {-100, -100}};

    // Create player
    Player* player = new Player{100.f, 100.f};

    // Camera 
    Camera2D camera = { 0 };
    camera.target = player->position;
    camera.offset = Vector2{ screenWidth / 2.0f, screenHeight / 2.0f }; 
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    // Main loop
    while (!WindowShouldClose()) {
        // Game logic
        if (!IsWindowMaximized()) {
            SetWindowSize(screenWidth, screenHeight);
        }

        camera.offset = Vector2{ GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };

        map->Update();
        player->Update(camera);

        // Drawings
        BeginDrawing(); 

            ClearBackground(DARKGRAY);

            BeginMode2D(camera);

                map->Draw(camera);
                player->Draw();

            EndMode2D();

        EndDrawing();
    }

    // Delete player
    delete player;

    // Delete map
    delete map;

    // Close window
    CloseWindow();

    return 0;
}