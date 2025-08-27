// Copyright (c) 2023 Dr. Matthias Hölzl. All rights reserved.

/***********************************************************************************
 * Example based on the raylib-intro-course, with support for emscripten.
 * CMake support is based on the CMakeLists.txt file from the raylib project.
 *
 * See <https://github.com/raysan5/raylib-intro-course> for the tutorial.
 */

#define __STDC_WANT_LIB_EXT1__ 1 // NOLINT(*-reserved-identifier)
#include "raylib.h"
#include "raymath.h"
#include <cstdio>
#include <filesystem>

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

// #define DEBUG_GAME_FLOW

#ifdef DEBUG_GAME_FLOW
#define LOGO_SCREEN_DURATION_IN_FRAMES 60
#define NUM_PLAYER_LIVES 2
#define BRICKS_LINES 2
#define BRICKS_PER_LINE 8
#define MASTER_VOLUME 0.0f
#else
#define LOGO_SCREEN_DURATION_IN_FRAMES 180
#define NUM_PLAYER_LIVES 5
#define BRICKS_LINES 5
#define BRICKS_PER_LINE 20
#define MASTER_VOLUME 0.1f
#endif

#define BRICKS_POSITION_Y 50
#define BRICK_RESISTANCE 1

#define SOUND_FX_VOLUME 0.2f
#define MUSIC_STREAM_VOLUME 0.6f

enum GameScreen { LOGO, TITLE, GAMEPLAY, ENDING };

struct Player {
    Vector2 position;
    Vector2 speed;
    Vector2 size;
    Rectangle bounds;
    int lives;
};

struct Ball {
    Vector2 position;
    Vector2 speed;
    float radius;
    bool active;
};

struct Brick {
    Vector2 position;
    Vector2 size;
    Rectangle bounds;
    int resistance;
    bool active;
};

GameScreen screen = LOGO;
Player player = {0};
Ball ball = {0};
Brick bricks[BRICKS_LINES][BRICKS_PER_LINE] = {0};
float brickScale = 1.0f;
int numActiveBricks = 0;

Texture2D texLogo;
Texture2D texBall;
Texture2D texPaddle;
Texture2D texBrick;

Font font;

Sound fxStart;
Sound fxBounce;
Sound fxExplode;

Music music;

void UpdateDrawFrame(); // Update and Draw one frame

float GetScreenHeightFloat() { return (float)GetScreenHeight(); }

float GetScreenWidthFloat() { return (float)GetScreenWidth(); }

int main(int argc, char* argv[]) {
    std::filesystem::path progPath = argv[0];
    std::filesystem::path resourcePath = progPath.parent_path() / "resources";

    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "PROJECT: BLOCKS GAME");

    // Note: Load resources after window initialization (OpenGL context is
    // required)
    texLogo = LoadTexture((resourcePath / "raylib_logo.png").string().c_str());
    texBall = LoadTexture((resourcePath / "ball.png").string().c_str());
    texPaddle = LoadTexture((resourcePath / "paddle.png").string().c_str());
    texBrick = LoadTexture((resourcePath / "brick.png").string().c_str());

    font = LoadFont((resourcePath / "setback.png").string().c_str());

#if !defined(PLATFORM_WEB)
    InitAudioDevice();

    SetMasterVolume(MASTER_VOLUME);

    fxStart = LoadSound((resourcePath / "start.wav").string().c_str());
    fxBounce = LoadSound((resourcePath / "bounce.wav").string().c_str());
    fxExplode = LoadSound((resourcePath / "explosion.wav").string().c_str());

    SetSoundVolume(fxStart, SOUND_FX_VOLUME);
    SetSoundVolume(fxBounce, SOUND_FX_VOLUME);
    SetSoundVolume(fxExplode, SOUND_FX_VOLUME);

    music = LoadMusicStream((resourcePath / "go-wild.mp3").string().c_str());

    SetMusicVolume(music, MUSIC_STREAM_VOLUME);

    PlayMusicStream(music);
#endif

    // Initialize player
    player.position = Vector2{GetScreenWidthFloat() / 2.0f,
                              GetScreenHeightFloat() * 7.0f / 8.0f};
    player.speed = Vector2{8.0f, 8.0f};
    player.size = Vector2{100, 24};
    player.lives = NUM_PLAYER_LIVES;

    // Initialize ball
    ball.radius = 10.0f;
    ball.active = false;
    ball.position = Vector2{player.position.x + player.size.x / 2 - ball.radius,
                            player.position.y - ball.radius * 2};
    ball.speed = Vector2{0.0f, 0.0f};

    // Initialize bricks
    brickScale = GetScreenWidthFloat() /
                 ((float)BRICKS_PER_LINE * (float)texBrick.width);
    for (int j = 0; j < BRICKS_LINES; ++j) {
        for (int i = 0; i < BRICKS_PER_LINE; ++i) {
            bricks[j][i].size = Vector2{(float)texBrick.width * brickScale,
                                        (float)texBrick.height * brickScale};
            bricks[j][i].position =
                Vector2{bricks[j][i].size.x * (float)i,
                        BRICKS_POSITION_Y + bricks[j][i].size.y * (float)j};
            bricks[j][i].bounds =
                Rectangle{bricks[j][i].position.x, bricks[j][i].position.y,
                          bricks[j][i].size.x, bricks[j][i].size.y};
            bricks[j][i].resistance = BRICK_RESISTANCE;
            bricks[j][i].active = true;
            ++numActiveBricks;
        }
    }

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        UpdateDrawFrame();
    }
#endif
    // Unload textures
    UnloadTexture(texBall);
    UnloadTexture(texPaddle);
    UnloadTexture(texBrick);

    UnloadFont(font);

    UnloadSound(fxStart);
    UnloadSound(fxBounce);
    UnloadSound(fxExplode);

    UnloadMusicStream(music);

    CloseAudioDevice();

    CloseWindow(); // Close window and OpenGL context

    return 0;
}

void UpdateDrawFrame() {

    static int framesCounter = 0;
    static int gameResult = -1; // -1 = Game not finished, 1 = Win, 0 = Lose
    static bool gamePaused = false;

    switch (screen) {
    case LOGO: {
        ++framesCounter;

        if (framesCounter > LOGO_SCREEN_DURATION_IN_FRAMES) {
            screen = TITLE;
            framesCounter = 0;
        }
        break;
    }
    case TITLE: {
        // Reset everything if we come back here after a game over
        if (gameResult != -1) {
            gameResult = -1;
            numActiveBricks = 0;
            for (int j = 0; j < BRICKS_LINES; ++j) { // NOLINT(*-loop-convert)
                for (int i = 0; i < BRICKS_PER_LINE; ++i) {
                    bricks[j][i].resistance = BRICK_RESISTANCE;
                    bricks[j][i].active = true;
                    ++numActiveBricks;
                }
            }
            player.lives = NUM_PLAYER_LIVES;
            player.position = Vector2{GetScreenWidthFloat() / 2.0f,
                                      GetScreenHeightFloat() * 7.0f / 8.0f};
            ball.position.x =
                player.position.x + player.size.x / 2 - ball.radius;
            ball.position.y = player.position.y - ball.radius * 2;
            ball.active = false;
        }

        ++framesCounter;
        if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP)) {
            screen = GAMEPLAY;
            PlaySound(fxStart);
        }
        break;
    }
    case GAMEPLAY: {
        if (IsKeyPressed('P')) {
            gamePaused = !gamePaused;
        }
        if (IsKeyPressed('Q')) {
            player.lives = 0;
            gameResult = numActiveBricks == 0 ? 1 : 0;
            screen = ENDING;
            break;
        }
        if (IsKeyPressed('W')) {
            for (int j = 0; j < BRICKS_LINES; ++j) { // NOLINT(*-loop-convert)
                for (int i = 0; i < BRICKS_PER_LINE; ++i) {
                    bricks[j][i].active = false;
                    --numActiveBricks;
                }
            }
            player.lives = 0;
            gameResult = 1;
            screen = ENDING;
            break;
        }
        if (IsKeyPressed('L')) {
            player.lives = 0;
            gameResult = 0;
            screen = ENDING;
            break;
        }
        if (IsKeyPressed('K')) {
            for (int j = 0; j < BRICKS_LINES; ++j) { // NOLINT(*-loop-convert)
                for (int i = 0; i < BRICKS_PER_LINE; ++i) {
                    int rand = GetRandomValue(0, 10);
                    if (rand < 5 && bricks[j][i].active) {
                        bricks[j][i].resistance = 0;
                        bricks[j][i].active = false;
                        --numActiveBricks;
                        if (numActiveBricks == 0) {
                            screen = ENDING;
                            gameResult = 1;
                            break;
                        }
                    }
                }
            }
        }

        if (!gamePaused) {
            if (IsKeyDown(KEY_LEFT)) {
                player.position.x -= player.speed.x;
            }
            if (IsKeyDown(KEY_RIGHT)) {
                player.position.x += player.speed.x;
            }

            if ((player.position.x) <= 0) {
                player.position.x = 0;
            }
            if ((player.position.x + player.size.x) >= GetScreenWidthFloat()) {
                player.position.x = GetScreenWidthFloat() - player.size.x;
            }

            player.bounds = Rectangle{player.position.x, player.position.y,
                                      player.size.x, player.size.y};

            if (ball.active) {
                // Ball movement logic
                ball.position.x += ball.speed.x;
                ball.position.y += ball.speed.y;

                // Collision logic: ball vs. screen limits
                if ((ball.position.x + 2 * ball.radius) >=
                    GetScreenWidthFloat()) {
                    ball.position.x = GetScreenWidthFloat() - 2 * ball.radius;
                    ball.speed.x *= -1;
                } else if (ball.position.x <= 0) {
                    ball.speed.x *= -1;
                    ball.position.x = 0;
                }

                if (ball.position.y <= 0) {
                    ball.speed.y *= -1;
                }

                // Collision logic: ball vs. player
                auto ballCenter = Vector2{ball.position.x + ball.radius,
                                          ball.position.y + ball.radius};
                if (CheckCollisionCircleRec(ballCenter, ball.radius,
                                            player.bounds)) {
                    if (ball.speed.y > 0) {
                        ball.speed.y *= -1;
                    }
                    ball.speed.x =
                        (ballCenter.x - player.position.x - player.size.x / 2) /
                        (player.size.x / 2) * 5.0f;
#if !defined(PLATFORM_WEB)
                    PlaySound(fxBounce);
#endif
                }

                // Collision logic: ball vs. bricks
                for (int j = 0; j < BRICKS_LINES; ++j) // NOLINT(*-loop-convert)
                {
                    for (int i = 0; i < BRICKS_PER_LINE; ++i) {
                        if (bricks[j][i].active) {
                            if (CheckCollisionCircleRec(ballCenter, ball.radius,
                                                        bricks[j][i].bounds)) {
                                --bricks[j][i].resistance;
                                if (bricks[j][i].resistance <= 0) {
                                    bricks[j][i].active = false;
                                    --numActiveBricks;
                                    if (numActiveBricks == 0) {
                                        screen = ENDING;
                                        gameResult = 1;
                                    }
#if !defined(PLATFORM_WEB)
                                    PlaySound(fxExplode);
#endif
                                } else {
#if !defined(PLATFORM_WEB)
                                    PlaySound(fxBounce);
#endif
                                }

                                ball.speed.y *= -1;
                                break;
                            }
                        }
                    }
                }

                // Game ending logic
                if ((ballCenter.y + ball.radius) >= GetScreenHeightFloat()) {
                    ball.position.x =
                        player.position.x + player.size.x / 2 - ball.radius;
                    ball.position.y = player.position.y - ball.radius * 2;
                    ball.active = false;
                    player.lives--;
                }

                if (player.lives <= 0) {
                    screen = ENDING;
                    player.lives = NUM_PLAYER_LIVES;
                    gameResult = numActiveBricks == 0 ? 1 : 0;
                    framesCounter = 0;
                }
            } else {
                // Reset ball position
                ball.position.x =
                    player.position.x + player.size.x / 2 - ball.radius;
                if (IsKeyPressed(KEY_SPACE)) {
                    const float angle =
                        (float)GetRandomValue(-300, 300) / 10.0f;
                    ball.speed =
                        Vector2Rotate(Vector2{0.0f, -5.0f}, angle * DEG2RAD);
                    ball.active = true;
                }
            }
        }
        break;
    }
    case ENDING: {
        ++framesCounter;

        if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP)) {
            screen = TITLE;
        }
        break;
    }
    }

    UpdateMusicStream(music);

    BeginDrawing();
    {
        ClearBackground(RAYWHITE);
        switch (screen) {

        case LOGO: {
            DrawTexture(texLogo, GetScreenWidth() / 2 - texLogo.width / 2,
                        GetScreenHeight() / 2 - texLogo.height / 2, WHITE);
            char text[80] = {0};
#if defined(__STDC_LIB_EXT1__)
            sprintf_s(text, 80, "WAIT for %.1f SECONDS...",
                      3.0f - (float)framesCounter / 60.0f);
#else
            sprintf(text, "WAIT for %.1f SECONDS...",
                    3.0f - (float)framesCounter / 60.0f);
#endif
            DrawText(text, GetScreenWidth() / 2 - MeasureText(text, 2),
                     GetScreenHeight() * 7 / 8, 20, GRAY);
            break;
        }
        case TITLE: {
            DrawTextEx(font, "BLOCKS", Vector2{100, 80}, 160, 10, MAROON);

            if ((framesCounter / 30) % 2) {
                DrawText("PRESS [ENTER] OR TAP TO START",
                         GetScreenWidth() / 2 -
                             MeasureText("PRESS [ENTER] OR TAP TO START", 20) /
                                 2,
                         GetScreenHeight() / 2 + 60, 20, DARKGRAY);
            }
            break;
        }
        case GAMEPLAY: {
            // Draw bricks
            for (int j = 0; j < BRICKS_LINES; ++j) {
                for (int i = 0; i < BRICKS_PER_LINE; ++i) {
                    if (bricks[j][i].active) {
                        if ((i + j) % 2 == 0) {
                            DrawTextureEx(texBrick, bricks[j][i].position, 0.0f,
                                          brickScale, GRAY);
                        } else {
                            DrawTextureEx(texBrick, bricks[j][i].position, 0.0f,
                                          brickScale, DARKGRAY);
                        }
                    }
                }
            }

            // Draw player
            DrawTextureEx(texPaddle, player.position, 0.0f, 1.0f, WHITE);
            // Draw ball
            DrawTextureEx(texBall, ball.position, 0.0f, 1.0f, MAROON);

            // Draw GUI: player lives
            for (int i = 0; i < player.lives; ++i) {
                DrawRectangle(20 + 40 * i, GetScreenHeight() - 30, 35, 10,
                              LIGHTGRAY);
            }

            // Draw pause message when required
            if (gamePaused) {
                DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(),
                              Fade(RAYWHITE, 0.8f));
                DrawText("GAME PAUSED",
                         GetScreenWidth() / 2 -
                             MeasureText("GAME PAUSED", 40) / 2,
                         GetScreenHeight() / 2 - 40, 40, GRAY);
            }
            break;
        }
        case ENDING: {
            if (gameResult == 0) {
                if (numActiveBricks > BRICKS_PER_LINE * BRICKS_LINES / 2) {
                    DrawTextEx(
                        font, "YOU LOSE!",
                        Vector2{GetScreenWidthFloat() / 2.0f -
                                    MeasureTextEx(font, "YOU_LOSE!", 80, 5).x /
                                        2.0f,
                                100},
                        80, 5, MAROON);

                } else {
                    DrawTextEx(
                        font, "GAME OVER",
                        Vector2{GetScreenWidthFloat() / 2.0f -
                                    MeasureTextEx(font, "GAME OVER", 80, 5).x /
                                        2.0f,
                                100},
                        80, 5, MAROON);
                }
            } else if (gameResult == 1) {
                DrawTextEx(
                    font, "YOU WIN!",
                    Vector2{GetScreenWidthFloat() / 2.0f -
                                MeasureTextEx(font, "YOU WIN!", 80, 5).x / 2.0f,
                            100},
                    80, 5, MAROON);
            } else {
                DrawTextEx(
                    font, "WHAT HAPPENED?",
                    Vector2{GetScreenWidthFloat() / 2.0f -
                                MeasureTextEx(font, "WHAT HAPPENED?", 80, 5).x /
                                    2.0f,
                            100},
                    80, 5, MAROON);
            }

            if ((framesCounter / 30) % 2 == 0) {
                DrawText("PRESS [ENTER] TO PLAY AGAIN",
                         GetScreenWidth() / 2 -
                             MeasureText("PRESS [ENTER] TO PLAY AGAIN", 20) / 2,
                         GetScreenHeight() / 2 + 80, 20, GRAY);
            }
            break;
        }
        }
    }
    EndDrawing();
}
