#include "raylib.h"
#include <emscripten/emscripten.h>
#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "level.h"
#include "collisions.h"
#include "boundedCamera.h"

Game game;
Level level;
BoundedCamera camera;

void UpdateFrame(){
	// Handle input for player animation
	if(IsKeyDown(KEY_D)){
		level.playerVelocity.x = 3.0f;
	} else if (IsKeyDown(KEY_A)){
		level.playerVelocity.x = -3.0f;
	} else {
		level.playerVelocity.x = 0.0f;
	}
	level.animPositions[level.playerAnimIndex].x += level.playerVelocity.x;
	Rectangle playerRect = {level.animPositions[level.playerAnimIndex].x, level.animPositions[level.playerAnimIndex].y, level.animations[level.playerAnimIndex].destination.width, level.animations[level.playerAnimIndex].destination.height};
	// Check for collisions
	if(CheckCollisionRecs(playerRect, level.leftBound)){
		handleSingleXCollision(&playerRect, level.leftBound);
	}
	if(CheckCollisionRecs(playerRect, level.rightBound)){
		handleSingleXCollision(&playerRect, level.rightBound);
	}
	// Adjust animation positions
	level.animPositions[level.playerAnimIndex].x = playerRect.x;
	// if(CheckCollisionRecs(platform, wall)){
	// 	handleCollision(&platform, &wall, &vel, &vel2, true, true);
	// }
	// Update Camera
	boundedCamera_updateCamera(&camera, playerRect, level.leftBound.x+level.leftBound.width-level.boundOverextension,level.rightBound.x+level.boundOverextension);
	BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawFPS(20, 20);
		// Camera bounds
		DrawRectangleRec(camera.leftBound, BLUE);
		DrawRectangleRec(camera.rightBound, BLUE);
		BeginMode2D(camera.camera);
			// DrawRectangleRec(wall, RED);
			DrawRectangleRec(level.leftBound, RED);
			DrawRectangleRec(level.rightBound, RED);
			// DrawRecDrawTextureTiled(game.textures[1], (Rectangle){0,0,40,20}, platform, (Vector2){0,0}, 0.0f, 2.0f, WHITE);
			level_renderAnimations(&level);
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
	// ================= CREATE LEVEL ======================
	Animation animations_one[2];
	level.animations = animations_one;
	animations_one[0] = animation_CreateAnimation(game.textures[0], 2, 50, 100, 0, 50, 50, 100);
	animations_one[1] = animation_CreateAnimation(game.textures[1], 1, 40, 20, 0, 50, 80, 40);
	animations_one[1].drawTiled = true;
	animations_one[1].tileScale = 2.0f;
	level.animNum = 2;
	Vector2 positions_one[2];
	level.animPositions = positions_one;
	positions_one[0] = (Vector2) {0, 0};
	positions_one[1] = (Vector2) {0, 100};
	level.playerAnimIndex = 0;
	level.playerVelocity = (Vector2) {0,0};
	level.leftBound = (Rectangle){-350,0,50, 600};
	level.rightBound = (Rectangle){900,0,50,600};
	level.boundOverextension = 10.0f;
	// ================= CAMERA SETUP ======================
	camera.camera.target = (Vector2){-200, 0};
	camera.camera.offset = (Vector2){0, 0};
	camera.camera.zoom = 1.0f;
	camera.camera.rotation = 0.0f;
	camera.leftBound = (Rectangle){0,0,150,600};
	camera.rightBound = (Rectangle){650,0,150,600};

	emscripten_set_main_loop(UpdateFrame, 0, 1);

	// Unload
	game_unloadTextures(game.textures, TEXTURE_NUM);

	CloseWindow();

	return 0;
}
