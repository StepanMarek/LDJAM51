#include "levels.h"
#include "level.h"
#include "gui.h"
#include "animation.h"
#include "raylib.h"
#include <stdio.h>

Level level_one(Game game){
	// Level level_alloc(int animNum, int collNum, int preludeNum, int playNum, int guiTextNum, int guiAnimNum, int enemies, int shields);
	Level level = level_alloc(7, 5, 0, 0, 0, 2, 1, 2);
	
	// Player
	level.animations[0] = animation_CreateAnimation(game.textures[2], 4, 50, 100, 0, 20, 50, 100);
	level.animPositions[0] = (Vector2) {0, 0};
	level.playerAnimIndex = 0;
	level.playerVelocity = (Vector2) {0,0};
	level.playerCollIndex = 0;
	level.collidingRects[0] = (Rectangle){0, 0, 50, 100};
	level.moveable[0] = true;
	level.collidingVels[0] = (Vector2){0,0};
	level.collAnimMap.keys[0] = 0;
	level.collAnimMap.vals[0] = 0;

	// Platform
	level.animations[1] = animation_CreateAnimation(game.textures[1], 1, 40, 20, 0, 50, 1200, 40);
	level.animations[1].drawTiled = true;
	level.animations[1].tileScale = 2.0f;
	level.animPositions[1] = (Vector2) {-300, 560};
	level.collidingRects[1] = (Rectangle){-300,560,1200,40};
	level.moveable[1] = false;
	level.collidingVels[1] = (Vector2){0,0};
	level.collAnimMap.keys[1] = 1;
	level.collAnimMap.vals[1] = 1;

	// Enemy
	level.animations[2] = animation_CreateAnimation(game.textures[3], 2, 50, 100, 0, 50, 50, 100);
	level.animPositions[2] = (Vector2){200,50};
	level.collidingRects[2] = (Rectangle){200,50,50,100};
	level.moveable[2] = true;
	level.collidingVels[2] = (Vector2){0,0};
	level.collAnimMap.keys[2] = 2;
	level.collAnimMap.vals[2] = 2;
	level.enemies[0] = 2;

	// Flare
	level.animations[3] = animation_CreateAnimation(game.textures[4], 5, 800, 100, 0, 20, 1250, 100);
	level.animations[3].drawTiled = true;
	level.animations[3].tileScale = 1.0f;
	level.animations[3].colormask = BLANK;
	level.animPositions[3].x = -350.0f;
	level.animPositions[3].y = 0.0f;
	level.flareAnimIndex = 3;

	// Shielding platform
	level.animations[4] = animation_CreateAnimation(game.textures[1], 1, 40, 30, 0, 50, 160,60);
	level.animations[4].drawTiled = true;
	level.animations[4].tileScale = 2;
	level.animPositions[4] = (Vector2) {200,200};
	level.collidingRects[3] = (Rectangle){200,200,160,40};
	level.moveable[3] = false;
	level.collidingVels[3] = (Vector2){0,0};
	level.collAnimMap.keys[3] = 3;
	level.collAnimMap.vals[3] = 4;
	level.shieldingPlatforms[0] = 3;
	
	// Shielding platform
	level.animations[5] = animation_CreateAnimation(game.textures[1], 1, 40, 30, 0, 50, 160,60);
	level.animations[5].drawTiled = true;
	level.animations[5].tileScale = 2;
	level.animPositions[5] = (Vector2) {50,450};
	level.collidingRects[4] = (Rectangle){50,450,160,40};
	level.moveable[4] = false;
	level.collidingVels[4] = (Vector2){0,0};
	level.collAnimMap.keys[4] = 4;
	level.collAnimMap.vals[4] = 5;
	level.shieldingPlatforms[1] = 4;
	
	// Door
	level.animations[6] = animation_CreateAnimation(game.textures[7], 1, 50, 100, 0, 50, 50, 100);
	level.animPositions[6].x = 850.0f;
	level.animPositions[6].y = 460.0f;
	level.doorAnimIndex = 6;

	// GUI
	level.gui.animations[0] = animation_CreateAnimation(game.textures[5], 8, 40, 40, 0, 100, 80, 80);
	level.gui.animPositions[0] = (Vector2) {700,20};
	level.gui.animations[1] = animation_CreateAnimation(game.textures[6], 1, 40, 40, 0, 100, 20, 100);
	level.gui.animPositions[1] = (Vector2) {730,110};
	level.guiHealth = 1;

	// Define level bounds
	level.leftBound = (Rectangle){-350,0,50, 600};
	level.rightBound = (Rectangle){900,0,50,600};
	level.boundOverextension = 10.0f;

	// Define preludes, requiems etc.
	level.preludeDone = true;
	level.playDone = false;
	level.requiemDone = false;
	
	return level;
}
