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
			// Set player direction
			game.currentLevel.animations[game.currentLevel.playerAnimIndex].startFrame = 0;
		} else if (IsKeyDown(KEY_A)){
			game.currentLevel.collidingVels[game.currentLevel.playerCollIndex].x = -3.0f;
			// Set player direction
			game.currentLevel.animations[game.currentLevel.playerAnimIndex].startFrame = 1;
		} else {
			game.currentLevel.collidingVels[game.currentLevel.playerCollIndex].x = 0.0f;
		}
		if(IsKeyPressed(KEY_W) && game.currentLevel.collidingVels[game.currentLevel.playerCollIndex].y == 0.0f){
			// Jump
			game.currentLevel.collidingVels[game.currentLevel.playerCollIndex].y = -12.0f;
		}
		// Acceleration due to gravity
		for(int i = 0; i < game.currentLevel.collNum; i++){
			if(game.currentLevel.moveable[i]){
				game.currentLevel.collidingVels[i].y += 0.5f;
			}
			// Then update positions
			game.currentLevel.collidingRects[i].x += game.currentLevel.collidingVels[i].x;
			game.currentLevel.collidingRects[i].y += game.currentLevel.collidingVels[i].y;
		}
		// Then, update enemy velocity in x towards player
		for(int i = 0; i < game.currentLevel.enemiesNum; i++){
			if(!game.currentLevel.enemiesAlive[i]){
				// Dead
				continue;
			}
			if(game.currentLevel.collidingRects[game.currentLevel.enemies[i]].x < game.currentLevel.collidingRects[game.currentLevel.playerCollIndex].x){
				game.currentLevel.collidingVels[game.currentLevel.enemies[i]].x = 2.0f;
			} else {
				game.currentLevel.collidingVels[game.currentLevel.enemies[i]].x = -2.0f;
			}
		}
		level_handleBoundsCollisions(&game.currentLevel);
		level_handleCollisions(&game.currentLevel);
		level_updateAnimPositions(&game.currentLevel);
		// Adjust animation positions
		boundedCamera_updateCamera(&camera, game.currentLevel.collidingRects[game.currentLevel.playerCollIndex], game.currentLevel.leftBound.x+game.currentLevel.leftBound.width-game.currentLevel.boundOverextension,game.currentLevel.rightBound.x+game.currentLevel.boundOverextension);
		// Update flare
		level_updateFlare(&game.currentLevel);
		printf("Player health : %i\n", game.currentLevel.playerHealth);
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
	const int TEXTURE_NUM = 6;
	const char * textureNames[TEXTURE_NUM];
	game.textureNames = textureNames;
	// Follows loading of textures
	textureNames[0] = "res/trial_anim.png";
	textureNames[1] = "res/platform.png";
	textureNames[2] = "res/player.png";
	textureNames[3] = "res/enemy.png";
	textureNames[4] = "res/flare.png";
	textureNames[5] = "res/flare_indicator.png";
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
