#include "raylib.h"
#include "animation.h"
#include <stdio.h>

Animation animation_CreateAnimation(Texture2D texture, int frames, int width, int height, int start, int upf, float renderWidth, float renderHeight){
	Animation anim;
	anim.numFrames = frames;
	anim.frameWidth = width;
	anim.frameHeight = height;
	anim.startFrame = start;
	anim.frame = (Rectangle){start * width, 0, width, height};
	anim.destination = (Rectangle){0, 0, renderWidth, renderHeight};
	anim.texture = texture;
	anim.updates = 0;
	anim.colormask = WHITE;
	anim.upf = upf;
	anim.drawTiled = false;
	anim.tileScale = 1.0f;
	return anim;
}

void animation_DrawFrame(Animation anim, int frameIndex, Vector2 position){
	// Find the correct frame
	anim.frame.x = (anim.startFrame + frameIndex) * anim.frameWidth;
	// Translate to destination
	anim.destination.x = position.x;
	anim.destination.y = position.y;
	if(anim.drawTiled){
		DrawTextureTiled(anim.texture, anim.frame, anim.destination, (Vector2){0,0}, 0.0f, anim.tileScale, anim.colormask);
	} else {
		DrawTexturePro(anim.texture, anim.frame, anim.destination, (Vector2){0,0}, 0.0f, anim.colormask);
	}
}

void animation_DrawUpdate(Animation * anim, Vector2 position){
	// Update frames
	printf("Rendering animation upf %i\n", anim->upf);
	anim->updates += 1;
	// Check where this lands us
	int targetFrame = anim->updates / anim->upf;
	if(targetFrame >= anim->numFrames){
		// Go back to beginning - LOOP
		// TODO : Differentiate between loop and other behaviour?
		anim->updates = 0;
		animation_DrawFrame(*anim, 0, position);
	} else {
		// Draw required frame
		animation_DrawFrame(*anim, targetFrame, position);
	}
}
