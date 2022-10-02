#include "raylib.h"
#include <emscripten/emscripten.h>
#include <stdio.h>
#include "game.h"
#include "level.h"
#include "collisions.h"
#include "boundedCamera.h"
#include "gui.h"
#include "levels.h"

Game game;
BoundedCamera camera;

void UpdateFrame(){
	if(game.state == LEVEL_PRELUDE){
		// Need to check both before and after prelude progress whether to end
		if(game.currentLevel.preludeDone){
			game.state = LEVEL_PLAY;
			return;
		}
		if(IsKeyPressed(KEY_SPACE)){
			level_progressPrelude(&game.currentLevel);
		}
		if(game.currentLevel.preludeDone){
			game.state = LEVEL_PLAY;
			return;
		}
	}
	if(game.state == LEVEL_PLAY){
		if(game.currentLevel.playDone){
			game.state = LEVEL_REQUIEM;
			return;
		}
		// Handle input for player animation
		if(IsKeyDown(KEY_D)){
			game.currentLevel.collidingVels[game.currentLevel.playerCollIndex].x = 3.0f;
		} else if (IsKeyDown(KEY_A)){
			game.currentLevel.collidingVels[game.currentLevel.playerCollIndex].x = -3.0f;
		} else {
			game.currentLevel.collidingVels[game.currentLevel.playerCollIndex].x = 0.0f;
		}
		if(IsKeyPressed(KEY_W) && game.currentLevel.collidingVels[game.currentLevel.playerCollIndex].y == 0.0f){
			// Jump
			game.currentLevel.collidingVels[game.currentLevel.playerCollIndex].y = -10.0f;
		}
		// Acceleration due to gravity
		game.currentLevel.collidingVels[game.currentLevel.playerCollIndex].y += 0.5f;
		game.currentLevel.collidingRects[game.currentLevel.playerCollIndex].x += game.currentLevel.collidingVels[game.currentLevel.playerCollIndex].x;
		game.currentLevel.collidingRects[game.currentLevel.playerCollIndex].y += game.currentLevel.collidingVels[game.currentLevel.playerCollIndex].y;
		level_handleBoundsCollisions(&game.currentLevel);
		level_handleCollisions(&game.currentLevel);
		level_updateAnimPositions(&game.currentLevel);
		// Adjust animation positions
		boundedCamera_updateCamera(&camera, game.currentLevel.collidingRects[game.currentLevel.playerCollIndex], game.currentLevel.leftBound.x+game.currentLevel.leftBound.width-game.currentLevel.boundOverextension,game.currentLevel.rightBound.x+game.currentLevel.boundOverextension);
		if(game.currentLevel.playDone){
			game.state = LEVEL_REQUIEM;
			return;
		}
	}
	if(game.state == LEVEL_REQUIEM){
		// Handle over to the next level
		game.currentLevel.requiemDone = true;
		game_nextLevel(&game);
		game.state = LEVEL_PRELUDE;
		return;
	}
	// Update Camera
	BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawFPS(20, 20);
		// Camera bounds
		// DrawRectangleRec(camera.leftBound, BLUE);
		// DrawRectangleRec(camera.rightBound, BLUE);
		// Draw GUI
		gui_renderTexts(&(game.currentLevel.gui), false);
		gui_renderAnimations(&(game.currentLevel.gui), false);
		BeginMode2D(camera.camera);
			// Draw level bounds
			// DrawRectangleRec(game.currentLevel.leftBound, RED);
			// DrawRectangleRec(game.currentLevel.rightBound, RED);
			level_renderAnimations(&game.currentLevel);
		EndMode2D();
	EndDrawing();
}

int main(){
	InitWindow(800,600, "simple example");

	GameState state = PRELUDE;
	// ================= CREATE TEXTURES =================
	const int TEXTURE_NUM = 4;
	const char * textureNames[TEXTURE_NUM];
	game.textureNames = textureNames;
	// Follows loading of textures
	textureNames[0] = "res/trial_anim.png";
	textureNames[1] = "res/platform.png";
	textureNames[2] = "res/player.png";
	textureNames[3] = "res/enemy.png";
	// Create texture pointers on stack
	Texture2D textures[TEXTURE_NUM];
	game.textures = textures;
	game_loadTextures(game.textureNames, TEXTURE_NUM, game.textures);
	const char * gameTexts[3];
	game.texts = gameTexts;
	game.texts[0] = "Text in global context";
	game.texts[1] = "Pres SPACE to start.";
	game.texts[2] = "First colony established around a pulsar star ...";
	game.textNum = 1;
	// ================= CREATE LEVEL ZERO =================
	Level level_start = level_zero(game);
	// ================= CREATE LEVEL ======================
	Level level = level_one(game);
	// Level level;
	// Animation animations_one[2];
	// level.animations = animations_one;
	// animations_one[0] = animation_CreateAnimation(game.textures[0], 2, 50, 100, 0, 50, 50, 100);
	// animations_one[1] = animation_CreateAnimation(game.textures[1], 1, 40, 20, 0, 50, 1200, 40);
	// animations_one[1].drawTiled = true;
	// animations_one[1].tileScale = 2.0f;
	// level.animNum = 2;
	// Vector2 positions_one[2];
	// level.animPositions = positions_one;
	// positions_one[0] = (Vector2) {0, 0};
	// positions_one[1] = (Vector2) {-300, 300};
	// level.playerAnimIndex = 0;
	// level.playerVelocity = (Vector2) {0,0};
	// level.leftBound = (Rectangle){-350,0,50, 600};
	// level.rightBound = (Rectangle){900,0,50,600};
	// level.boundOverextension = 10.0f;
	// Rectangle collRects[2];
	// level.collidingRects = collRects;
	// level.collidingRects[0] = (Rectangle){0, 0, 50, 100};
	// level.collidingRects[1] = (Rectangle){-300,300,1200,40};
	// bool moveable[2];
	// level.moveable = moveable;
	// level.moveable[0] = true;
	// level.moveable[1] = false;
	// Vector2 velocities_one[2];
	// level.collidingVels = velocities_one;
	// level.collidingVels[0] = (Vector2){0,0};
	// level.collidingVels[1] = (Vector2){0,0};
	// level.collNum = 2;
	// level.playerCollIndex = 0;
	// int levelMapKeys[2];
	// int levelMapVals[2];
	// level.collAnimMap.keys = levelMapKeys;
	// level.collAnimMap.vals = levelMapVals;
	// level.collAnimMap.keys[0] = 0;
	// level.collAnimMap.keys[1] = 1;
	// level.collAnimMap.vals[0] = 0;
	// level.collAnimMap.vals[1] = 1;
	// level.preludeDone = true;
	// level.playDone = false;
	// level.requiemDone = false;
	// ================= CAMERA SETUP ======================
	camera.camera.target = (Vector2){-200, 0};
	camera.camera.offset = (Vector2){0, 0};
	camera.camera.zoom = 1.0f;
	camera.camera.rotation = 0.0f;
	camera.leftBound = (Rectangle){0,0,150,600};
	camera.rightBound = (Rectangle){650,0,150,600};
	// ================= GUI SETUP =================
	// GuiManager gui;
	// const char * texts[1];
	// gui.texts = texts;
	// gui.textNum = 1;
	// Vector2 textPositions[1];
	// gui.textPositions = textPositions;
	// int textSizes[1];
	// gui.textSizes = textSizes;
	// Color textColors[1];
	// gui.textColors = textColors;	
	// gui_constructText(&gui, "GUI Text", 0);
	// Animation gui_anims[1];
	// gui.animations = gui_anims;
	// gui.animNum = 1;
	// Vector2 anim_pos[1];
	// gui.animPositions = anim_pos;
	// gui.animPositions[0] = (Vector2){300,200};
	// gui_constructAnimationStatic(&gui, 0, game.textures[0], 50, 100, 1, 200, 400);
	// level.gui = &gui;

	// Set up current and next level
	game.currentLevel = level_start;
	game.nextLevel = level;
	Level gameLevels[2];
	gameLevels[0] = level_start;
	gameLevels[1] = level;
	game.levels = gameLevels;
	game.levelNum = 2;
	game.levelIndex = 0;

	game.state = LEVEL_PRELUDE;

	emscripten_set_main_loop(UpdateFrame, 0, 1);

	// Unload
	level_free(level);
	level_free(level_start);
	game_unloadTextures(game.textures, TEXTURE_NUM);

	CloseWindow();

	return 0;
}
