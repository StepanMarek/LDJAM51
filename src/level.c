#include "raylib.h"
#include "animation.h"
#include "level.h"
#include "collisions.h"

int level_map(Level level, int key){
	for(int i = 0; i < level.collNum; i++){
		if(level.collAnimMap.keys[i] == key) return level.collAnimMap.vals[i];
	}
	// No match
	return -1;
}

void level_renderAnimations(Level * level){
	// For each animation, draw it at given position
	for(int i = 0; i < level->animNum; i++){
		// Draw animation at its corresponding position
		animation_DrawUpdate(&(level->animations[i]), level->animPositions[i]);
	}
}

void level_handleBoundsCollisions(Level * level){
	// For each colliding rect, handle collisions with either bound
	for(int i = 0; i < level->collNum; i++){
		// Only makes sense for movable - others can be skipped
		if(!(level->moveable[i])) continue;
		// Handle left
		if(CheckCollisionRecs(level->collidingRects[i], level->leftBound)){
			handleSingleXCollision(&(level->collidingRects[i]), level->leftBound);
		}
		// Handle right
		if(CheckCollisionRecs(level->collidingRects[i], level->rightBound)){
			handleSingleXCollision(&(level->collidingRects[i]), level->rightBound);
		}
	}
}
void level_handleCollisions(Level * level){
	// Unlike in the previous case, these collisions are more involved
	for(int i = 0; i < level->collNum;i++){
		// TODO : Only need to check pairs once?
		for(int j=i+1; j < level->collNum;j++){
			// Check pair
			if(CheckCollisionRecs(level->collidingRects[i], level->collidingRects[j])){
				// Proceeed to handling the collision
				handleCollision(&(level->collidingRects[i]), &(level->collidingRects[j]), &(level->collidingVels[i]), &(level->collidingVels[j]), level->moveable[i], level->moveable[j]);
			}
		}
	}
}
void level_updateAnimPositions(Level * level){
	// Used after all collisions are sorted out
	int mappedI;
	for(int i = 0; i < level->collNum; i++){
		mappedI = level_map(*level, i);
		if(mappedI == -1){
			// This means that the colliding rect is not mapped to a corresponding texture
			continue;
		}
		level->animPositions[mappedI].x = level->collidingRects[i].x;
		level->animPositions[mappedI].y = level->collidingRects[i].y;
	}
}

void level_progressPrelude(Level * level){
	if(level->preludeIndex + 1 >= level->preludeNum){
		// Prelude done
		level->preludeIndex = 0;
		level->preludeDone = true;
		level->gui = level->playGui;
	} else {
		// Progress to the next gui
		level->preludeIndex += 1;
		level->gui = level->preludeGuis[level->preludeIndex];
	}
}
