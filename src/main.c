#include "raylib.h"
#include <emscripten/emscripten.h>
#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "collisions.h"
#include "boundedCamera.h"

Game game;
BoundedCamera camera;
Vector2 vel = {0.0f, 0.0f};
Vector2 vel2 = {0.0f, 0.0f};
Rectangle wall = {400,10,20,60};
Rectangle platform = {20, 40, 300, 40};

void UpdateFrame(){
	if(IsKeyDown(KEY_D)){
		vel.x = 1.0f;
	} else if(IsKeyDown(KEY_A)){
		vel.x = -1.0f;
	} else {
		vel.x = 0.0f;
	}
	platform.x += vel.x;
	wall.x += vel2.x;
	// Check for collisions
	// if(CheckCollisionRecs(platform, wall)){
	// 	handleCollision(&platform, &wall, &vel, &vel2, true, true);
	// }
	// Update Camera
	boundedCamera_updateCamera(&camera, platform, -200,820);
	BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawFPS(20, 20);
		DrawRectangleRec(camera.leftBound, BLUE);
		DrawRectangleRec(camera.rightBound, BLUE);
		BeginMode2D(camera.camera);
			DrawRectangleRec(wall, RED);
			DrawTextureTiled(game.textures[1], (Rectangle){0,0,40,20}, platform, (Vector2){0,0}, 0.0f, 2.0f, WHITE);
		EndMode2D();
	EndDrawing();
}

int main(){
	InitWindow(800,600, "simple example");

	GameState state = PRELUDE;
	// ================= CREATE TEXTURES =================
	const int TEXTURE_NUM = 2;
	const char * textureNames[TEXTURE_NUM];
	game.textureNames = textureNames;
	// Follows loading of textures
	textureNames[0] = "res/trial_anim.png";
	textureNames[1] = "res/platform.png";
	// Create texture pointers on stack
	Texture2D textures[TEXTURE_NUM];
	game.textures = textures;
	game_loadTextures(game.textureNames, TEXTURE_NUM, game.textures);
	// ================= CREATE ANIMATIONS =================
	const int ANIM_NUM = 1;
	Animation animations[ANIM_NUM];
	game.animations = animations;
	game.animations[0] = animation_CreateAnimation(game.textures[0], 2, 50, 100, 0, 20);
	camera.camera.target = (Vector2){-100, -100};
	camera.camera.offset = (Vector2){0, 0};
	camera.camera.zoom = 1.0f;
	camera.camera.rotation = 0.0f;
	camera.leftBound = (Rectangle){0,0,50,600};
	camera.rightBound = (Rectangle){750,0,50,600};

	emscripten_set_main_loop(UpdateFrame, 0, 1);

	// Unload
	game_unloadTextures(game.textures, TEXTURE_NUM);

	CloseWindow();

	return 0;
}
