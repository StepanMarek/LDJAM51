#include "raylib.h"
#include <emscripten/emscripten.h>
#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "level.h"
#include "collisions.h"
#include "boundedCamera.h"
#include "gui.h"

Game game;
Level level;
BoundedCamera camera;
GuiManager gui;

void UpdateFrame(){
	// Handle input for player animation
	if(IsKeyDown(KEY_D)){
		level.collidingVels[level.playerCollIndex].x = 3.0f;
	} else if (IsKeyDown(KEY_A)){
		level.collidingVels[level.playerCollIndex].x = -3.0f;
	} else {
		level.collidingVels[level.playerCollIndex].x = 0.0f;
	}
	if(IsKeyPressed(KEY_W) && level.collidingVels[level.playerCollIndex].y == 0.0f){
		// Jump
		level.collidingVels[level.playerCollIndex].y = -10.0f;
	}
	// Acceleration due to gravity
	level.collidingVels[level.playerCollIndex].y += 0.5f;
	level.collidingRects[level.playerCollIndex].x += level.collidingVels[level.playerCollIndex].x;
	level.collidingRects[level.playerCollIndex].y += level.collidingVels[level.playerCollIndex].y;
	// Rectangle playerRect = {level.animPositions[level.playerAnimIndex].x, level.animPositions[level.playerAnimIndex].y, level.animations[level.playerAnimIndex].destination.width, level.animations[level.playerAnimIndex].destination.height};
	// // Check for collisions
	// if(CheckCollisionRecs(playerRect, level.leftBound)){
	// 	handleSingleXCollision(&playerRect, level.leftBound);
	// }
	// if(CheckCollisionRecs(playerRect, level.rightBound)){
	// 	handleSingleXCollision(&playerRect, level.rightBound);
	// }
	level_handleBoundsCollisions(&level);
	level_handleCollisions(&level);
	level_updateAnimPositions(&level);
	// Adjust animation positions
	// Update Camera
	boundedCamera_updateCamera(&camera, level.collidingRects[level.playerCollIndex], level.leftBound.x+level.leftBound.width-level.boundOverextension,level.rightBound.x+level.boundOverextension);
	BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawFPS(20, 20);
		// Camera bounds
		// DrawRectangleRec(camera.leftBound, BLUE);
		// DrawRectangleRec(camera.rightBound, BLUE);
		// Draw GUI
		gui_renderTexts(&gui);
		gui_renderAnimations(&gui);
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
	animations_one[1] = animation_CreateAnimation(game.textures[1], 1, 40, 20, 0, 50, 1200, 40);
	animations_one[1].drawTiled = true;
	animations_one[1].tileScale = 2.0f;
	level.animNum = 2;
	Vector2 positions_one[2];
	level.animPositions = positions_one;
	positions_one[0] = (Vector2) {0, 0};
	positions_one[1] = (Vector2) {-300, 300};
	level.playerAnimIndex = 0;
	level.playerVelocity = (Vector2) {0,0};
	level.leftBound = (Rectangle){-350,0,50, 600};
	level.rightBound = (Rectangle){900,0,50,600};
	level.boundOverextension = 10.0f;
	Rectangle collRects[2];
	level.collidingRects = collRects;
	level.collidingRects[0] = (Rectangle){0, 0, 50, 100};
	level.collidingRects[1] = (Rectangle){-300,300,1200,40};
	bool moveable[2];
	level.moveable = moveable;
	level.moveable[0] = true;
	level.moveable[1] = false;
	Vector2 velocities_one[2];
	level.collidingVels = velocities_one;
	level.collidingVels[0] = (Vector2){0,0};
	level.collidingVels[1] = (Vector2){0,0};
	level.collNum = 2;
	level.playerCollIndex = 0;
	int levelMapKeys[2];
	int levelMapVals[2];
	level.collAnimMap.keys = levelMapKeys;
	level.collAnimMap.vals = levelMapVals;
	level.collAnimMap.keys[0] = 0;
	level.collAnimMap.keys[1] = 1;
	level.collAnimMap.vals[0] = 0;
	level.collAnimMap.vals[1] = 1;
	// ================= CAMERA SETUP ======================
	camera.camera.target = (Vector2){-200, 0};
	camera.camera.offset = (Vector2){0, 0};
	camera.camera.zoom = 1.0f;
	camera.camera.rotation = 0.0f;
	camera.leftBound = (Rectangle){0,0,150,600};
	camera.rightBound = (Rectangle){650,0,150,600};
	// ================= GUI SETUP =================
	const char * texts[1];
	gui.texts = texts;
	gui.textNum = 1;
	Vector2 textPositions[1];
	gui.textPositions = textPositions;
	int textSizes[1];
	gui.textSizes = textSizes;
	Color textColors[1];
	gui.textColors = textColors;	
	gui_constructText(&gui, "GUI Text", 0);
	Animation gui_anims[1];
	gui.animations = gui_anims;
	gui.animNum = 1;
	Vector2 anim_pos[1];
	gui.animPositions = anim_pos;
	gui.animPositions[0] = (Vector2){300,200};
	gui_constructAnimationStatic(&gui, 0, game.textures[0], 50, 100, 1, 200, 400);

	emscripten_set_main_loop(UpdateFrame, 0, 1);

	// Unload
	game_unloadTextures(game.textures, TEXTURE_NUM);

	CloseWindow();

	return 0;
}
