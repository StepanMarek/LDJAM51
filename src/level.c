#include "animation.h"
#include "level.h"

void level_renderAnimations(Level * level){
	// For each animation, draw it at given position
	for(int i = 0; i < level->animNum; i++){
		// Draw animation at its corresponding position
		animation_DrawUpdate(&(level->animations[i]), level->animPositions[i]);
	}
}
