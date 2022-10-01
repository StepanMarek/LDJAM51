#include "raylib.h"
#include "animation.h"

Animation animation_CreateAnimation(Texture2D texture, int frames, int width, int height, int start, int upf){
	Animation anim;
	anim.numFrames = frames;
	anim.frameWidth = width;
	anim.frameHeight = height;
	anim.startFrame = start;
	anim.frame = (Rectangle){start * width, 0, width, height};
	anim.texture = texture;
	anim.updates = 0;
	anim.pUpdates = &(anim.updates);
	anim.upf = upf;
	return anim;
}

void animation_DrawFrame(Animation anim, int frameIndex, Vector2 position, Color color){
	anim.frame.x = (anim.startFrame + frameIndex) * anim.frameWidth;
	DrawTextureRec(anim.texture, anim.frame, position, color);
}

void animation_DrawUpdate(Animation anim, Vector2 position, Color color, int * pUpdates){
	// Update frames both on local stack and on outer stack
	(*pUpdates) += 1;
	int updates = (*pUpdates);
	// Check where this lands us
	int targetFrame = updates / anim.upf;
	if(targetFrame >= anim.numFrames){
		// Go back to beginning - LOOP
		// TODO : Differentiate between loop and other behaviour?
		(*pUpdates) = 0;
		animation_DrawFrame(anim, 0, position, color);
	} else {
		// Draw required frame
		animation_DrawFrame(anim, targetFrame, position, color);
	}
}
