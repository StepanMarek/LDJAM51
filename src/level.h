#include "raylib.h"
#include "animation.h"
#ifndef GAME_LEVEL
#define GAME_LEVEL

typedef struct {
	int * keys;
	int * vals;
} IntIntMap;

typedef struct {
	Animation * animations;
	int animNum;
	Vector2 * animPositions;
	int playerAnimIndex;
	Vector2 playerVelocity;
	Rectangle leftBound;
	Rectangle rightBound;
	// Camera is allowed to move slightly out of the level
	float boundOverextension;
	Rectangle * collidingRects;
	Vector2 * collidingVels;
	bool * moveable;
	int collNum;
	IntIntMap collAnimMap;
	int playerCollIndex;
} Level;

int level_map(Level level, int key);

void level_renderAnimations(Level * level);
void level_handleBoundsCollisions(Level * level);
void level_handleCollisions(Level * level);
void level_updateAnimPositions(Level * level);
#endif
