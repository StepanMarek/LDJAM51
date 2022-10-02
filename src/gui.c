#include "raylib.h"
#include "gui.h"
#include "animation.h"

void gui_renderTexts(GuiManager * gui){
	for(int i = 0; i < gui->textNum; i++){
		DrawText(gui->texts[i], gui->textPositions[i].x, gui->textPositions[i].y, gui->textSizes[i], gui->textColors[i]);
	}
}

void gui_constructTextWithParams(GuiManager * gui, const char * text, int textIndex, Vector2 textPosition, int textSize, Color textColor){
	gui->texts[textIndex] = text;
	gui->textPositions[textIndex].x = textPosition.x;
	gui->textPositions[textIndex].y = textPosition.y;
	gui->textSizes[textIndex] = textSize;
	gui->textColors[textIndex] = textColor;
}

void gui_constructText(GuiManager * gui, const char * text, int textIndex){
	gui_constructTextWithParams(gui, text, textIndex, (Vector2){0,0}, 20, BLACK);
	
}

void gui_renderAnimations(GuiManager * gui){
	for(int i = 0; i < gui->animNum; i++){
		animation_DrawUpdate(&(gui->animations[i]), gui->animPositions[i]);
	}	
}

void gui_constructAnimationWithParams(GuiManager * gui, int animIndex, Texture2D texture, int numFrames, int frameWidth, int frameHeight, int startFrame, int upf, float renderWidth, float renderHeight){
	gui->animations[animIndex] =  animation_CreateAnimation(texture, numFrames, frameWidth, frameHeight, startFrame, upf, renderWidth, renderHeight);
}

void gui_constructAnimationStatic(GuiManager * gui, int animIndex, Texture2D texture, int frameWidth, int frameHeight, int frameIndex, float renderWidth, float renderHeight){
	// TODO : Figure out what to do with upf for static animations?
	gui_constructAnimationWithParams(gui, animIndex, texture, 1, frameWidth, frameHeight, 0, 100, renderWidth, renderHeight);
}
