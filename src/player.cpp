#include "player.h"

Player::Player(float StartX, float StartY) {
    position = {StartX, StartY};
    angle = 0.0f;
    movementSpeed = 200.0f;
    target = GetMousePosition();
    range = 300;
    isShotting = false;
    shotPos = position;
    shotStartPos = position;
    shotSpeed = 600.0f;
    level = 0;
    health = 100;
    playerTexture = LoadTexture("assets/PNG/Man Blue/manBlue_gun.png");
}

Player::~Player() {
    UnloadTexture(playerTexture);
}

void Player::Move() {
    float deltaTime = GetFrameTime();

    if(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))    {position.y -= movementSpeed * deltaTime;}
    if(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))  {position.x -= movementSpeed * deltaTime;}
    if(IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))  {position.y += movementSpeed * deltaTime;}
    if(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {position.x += movementSpeed * deltaTime;}
}

void Player::Aim() {
    target = GetMousePosition();

    if ((target.x - position.x) > range) {target.x = position.x + range;}
    if ((target.x - position.x) < range * -1) {target.x = position.x - range;}
    if ((target.y - position.y) > range) {target.y = position.y + range;}
    if ((target.y - position.y) < range * -1) {target.y = position.y - range;}

    float dx = target.x - position.x;
    float dy = target.y - position.y;

    angle = atan2f(dy, dx) * RAD2DEG;
}

void Player::Shot() {
    float deltaTime = GetFrameTime();

    if (!isShotting && IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        isShotting = true;
        shotPos = position;
        shotAngle = angle; 
        shotStartPos = position;
    }

    if (isShotting) {
        float angleRad = shotAngle * DEG2RAD;

        shotPos.x += cosf(angleRad) * shotSpeed * deltaTime;
        shotPos.y += sinf(angleRad) * shotSpeed * deltaTime;

        if (Vector2Distance(shotStartPos, shotPos) >= range) {
            isShotting = false;
        }
    }
}

void Player::Update() {
    Move();
    Aim(); 
    Shot();
}

void Player::Draw() {
    Rectangle source = {0.0f, 0.0f, (float) playerTexture.width, (float) playerTexture.height};
    Rectangle dest = {position.x, position.y, (float) playerTexture.width, (float) playerTexture.height};
    Vector2 origin = {playerTexture.width / 2.0f, playerTexture.height / 2.0f};
    DrawTexturePro(playerTexture, source, dest, origin, angle, WHITE);

    DrawLineV(position, target, LIGHTGRAY);
    if (isShotting) {
        DrawCircleV(shotPos, 6, RED);
    }
}