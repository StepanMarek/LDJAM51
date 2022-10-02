#include "levels.h"
#include "level.h"
#include "gui.h"
#include "animation.h"
#include "raylib.h"
#include <stdio.h>

Level level_one(Game game){
	// Level level_alloc(int animNum, int collNum, int preludeNum, int playNum, int guiTextNum, int guiAnimNum);
	Level level = level_alloc(4, 3, 0, 0, 0, 0, 1);
	
	// Player
	level.animations[0] = animation_CreateAnimation(game.textures[2], 1, 50, 100, 0, 50, 50, 100);
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
	level.animPositions[1] = (Vector2) {-300, 300};
	level.collidingRects[1] = (Rectangle){-300,300,1200,40};
	level.moveable[1] = false;
	level.collidingVels[1] = (Vector2){0,0};
	level.collAnimMap.keys[1] = 1;
	level.collAnimMap.vals[1] = 1;

	// Enemy
	level.animations[2] = animation_CreateAnimation(game.textures[3], 1, 50, 100, 0, 50, 50, 100);
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
	level.animPositions[3].x = -350.0f;
	level.animPositions[3].y = 0.0f;

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
