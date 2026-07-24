#include "player.h"
#include "raymath.h"
#include <math.h>

Player::Player(float StartX, float StartY) {
    position = {StartX, StartY};
    angle = 0.0f;
    movementSpeed = 200.0f;
    target = position; 
    range = 300;
    isShooting = false;
    shotPos = position;
    shotStartPos = position;
    shotDir = {0, 0};
    shotSpeed = 600.0f;
    level = 0;
    health = 100;
    playerTexture = LoadTexture("assets/PNG/manBlue_gun.png");
}

Player::~Player() {
    // Unloading texture
    UnloadTexture(playerTexture);
}

void Player::Move() {
    float deltaTime = GetFrameTime();

    // Getting movement direction based on user input
    Vector2 moveDir = {0.0f, 0.0f};

    if(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))    {moveDir.y -= 1.0f;}
    if(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))  {moveDir.x -= 1.0f;}
    if(IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))  {moveDir.y += 1.0f;}
    if(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {moveDir.x += 1.0f;}

    // Check if the player is moving to normalize the vector (prevents faster diagonal movement)
    if (Vector2Length(moveDir) > 0) {
        moveDir = Vector2Normalize(moveDir);
    }

    // Updating position
    position.x += moveDir.x * movementSpeed * deltaTime;
    position.y += moveDir.y * movementSpeed * deltaTime;

    // Setting map limit
    if (position.x >= 2460) {position.x = 2460;}
    if (position.y >= 2460) {position.y = 2460;}
    if (position.x <= -100) {position.x = -100;}
    if (position.y <= -100) {position.y = -100;}
}

void Player::Aim(Camera2D camera) {
    // Get mouse position in world space using updated camera
    Vector2 mouseScreenPos = GetMousePosition();
    Vector2 worldMouse = GetScreenToWorld2D(mouseScreenPos, camera);

    // Get displacement from current player position
    Vector2 displacement = Vector2Subtract(worldMouse, position);

    // Get angle in which the player is aiming
    angle = atan2f(displacement.y, displacement.x);

    // Calculate target position based on range
    Vector2 direction = Vector2Normalize(displacement);
    target = Vector2Add(position, Vector2Scale(direction, range));
}

void Player::Shot() {
    float deltaTime = GetFrameTime();

    // Check if the player is not already shooting and the left mouse button is pressed
    if (!isShooting && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        isShooting = true;
        shotPos = position;
        shotStartPos = position;
        
        // Calculate normalized direction vector at the exact moment of shooting
        shotDir = Vector2Normalize(Vector2Subtract(target, position));
    }

    // Check if the bullet is traveling in this moment
    if (isShooting) {
        // Update bullet position along the fixed direction vector
        shotPos.x += shotDir.x * shotSpeed * deltaTime;
        shotPos.y += shotDir.y * shotSpeed * deltaTime;

        // Check if the bullet reached maximum range from spawn point
        if (Vector2Distance(shotStartPos, shotPos) >= range) {
            isShooting = false;
        }
    }
}

void Player::Update(Camera2D &camera) {
    // Move player first
    Move();
    
    // Update camera target immediately so Aim uses the exact current frame transformation
    camera.target = position; 
    
    // Calculate aim and shot after position and camera are synced
    Aim(camera); 
    Shot();
}

void Player::Draw() {
    // Draw the player shadow
    DrawCircleV({position.x - 5, position.y}, 20.0f, LIGHTGRAY);

    Rectangle source = {0.0f, 0.0f, (float)playerTexture.width, (float)playerTexture.height};
    Rectangle dest = {position.x, position.y, (float)playerTexture.width, (float)playerTexture.height};
    Vector2 origin = {playerTexture.width / 2.0f, playerTexture.height / 2.0f};
    
    // Draw the player
    DrawTexturePro(playerTexture, source, dest, origin, angle * RAD2DEG, WHITE);
    
    // Draw the aim
    if (!isShooting) {
    DrawLineV(position, target, LIGHTGRAY);
    }

    // Draw the bullet if the player is shooting
    if (isShooting) {
        DrawCircleV(shotPos, 6, BLUE);
    }

    // Draw the player text
    DrawText("ME", position.x - 15, position.y - 40, 15, BLUE);
}