#include "raylib.h"
#ifndef GAME_COLLISIONS
#define GAME_COLLISIONS
void handleCollision(Rectangle * rect1, Rectangle * rect2, Vector2 * vel1, Vector2 * vel2, bool move1, bool move2);
float getCollisionSingleXOffset(Rectangle rect1, Rectangle rect2);
#endif
