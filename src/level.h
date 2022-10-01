#include "raylib.h"
#include "animation.h"
#ifndef GAME_LEVEL
#define GAME_LEVEL
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
	bool * movable;
	int playerCollideIndex;
} Level;

void level_renderAnimations(Level * level);
#endif
