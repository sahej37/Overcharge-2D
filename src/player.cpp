#include "player.h"

Player::Player(float StartX, float StartY) {
    position = {StartX, StartY};
    speed = 200.f;
    level = 0;
    health = 100;
}

void Player::Update() {
    float deltaTime = GetFrameTime();

    if(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {position.y -= speed * deltaTime;}
    if(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {position.x -= speed * deltaTime;}
    if(IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {position.y += speed * deltaTime;}
    if(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {position.x += speed * deltaTime;}
}

void Player::Draw() {
    DrawCircleV(position, 20, BLUE);
}