#include "raylib.h"
#include "animation.h"
#ifndef GAME_LEVEL
#define GAME_LEVEL
typedef struct {
	Animation * animations;
	int animNum;
	Vector2 * animPositions;
} Level;

void level_renderAnimations(Level * level);
#endif
