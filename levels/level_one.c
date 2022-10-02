#include "levels.h"
#include "level.h"
#include "gui.h"
#include "animation.h"
#include "raylib.h"
#include <stdio.h>

Level level_one(Game game){
	Level level = level_alloc(2, 2, 0, 0, 1, 1);
	
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

	// Define level bounds
	level.leftBound = (Rectangle){-350,0,50, 600};
	level.rightBound = (Rectangle){900,0,50,600};
	level.boundOverextension = 10.0f;

	// GUI setup
	gui_constructText(&(level.gui), game.texts[0], 0);
	level.gui.textPositions[0].x = 100.0;
	level.gui.animPositions[0] = (Vector2){300,200};
	gui_constructAnimationStatic(&(level.gui), 0, game.textures[0], 50, 100, 1, 200, 400);

	// Define preludes, requiems etc.
	level.preludeDone = true;
	level.playDone = false;
	level.requiemDone = false;
	
	return level;
}
