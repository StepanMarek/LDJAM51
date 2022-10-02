#include "raylib.h"
#include "animation.h"
#include "level.h"
#include "collisions.h"
#include <stdio.h>
#include <stdlib.h>

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
		// If there is a play guy, load it
		if(level->playNum > 0){
			level->gui = level->playGuis[0];
		}
	} else {
		// Progress to the next gui
		level->preludeIndex += 1;
		level->gui = level->preludeGuis[level->preludeIndex];
	}
}

void level_free(Level level){
	// Free the array of animations
	free(level.animations);
	// Free the animation positions
	free(level.animPositions);
	// Free array of colliding rects
	free(level.collidingRects);
	// Free array of colliding velocities
	free(level.collidingVels);
	// Free array of movable identifiers
	free(level.moveable);
	// Free both keys and values of coll->anim map
	free(level.collAnimMap.keys);
	free(level.collAnimMap.vals);
	// Call necessary frees on gui
	gui_free(level.gui);
	// Now, free each other defined gui
	for(int i=0; i < level.preludeNum; i++){
		gui_free(level.preludeGuis[i]);
	}
	for(int i=0; i < level.playNum; i++){
		gui_free(level.playGuis[i]);
	}
}
Level level_alloc(int animNum, int collNum, int preludeNum, int playNum, int guiTextNum, int guiAnimNum){
	Level level;
	level.animations = (Animation *) malloc(sizeof(Animation) * animNum);
	level.animPositions = (Vector2 *) malloc(sizeof(Vector2) * animNum);
	level.collidingRects = (Rectangle *) malloc(sizeof(Rectangle) * collNum);
	level.collidingVels = (Vector2 *) malloc(sizeof(Vector2) * collNum);
	level.moveable = (bool *) malloc(sizeof(bool) * collNum);
	level.collAnimMap.keys = (int *) malloc(sizeof(int) * collNum);
	level.collAnimMap.vals = (int *) malloc(sizeof(int) * collNum);
	// Automatically initiate to identity mapping
	for(int i = 0; i < collNum; i++){
		level.collAnimMap.keys[i] = i;
		level.collAnimMap.vals[i] = i;
	}
	// Automatically create specified gui, others have to be allocated manually
	level.gui = gui_alloc(guiTextNum, guiAnimNum);
	level.preludeGuis = (GuiManager *) malloc(sizeof(GuiManager) * preludeNum);
	level.playGuis = (GuiManager *) malloc(sizeof(GuiManager) * playNum);
	// Write known values
	level.animNum = animNum;
	level.collNum = collNum;
	level.preludeNum = preludeNum;
	level.playNum = playNum;
	return level;

}
