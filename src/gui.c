#include "raylib.h"
#include "gui.h"
#include "animation.h"
#include <stdio.h>
#include <stdlib.h>

void gui_renderTexts(GuiManager * gui, bool debug){
	if(debug) printf("Hello?\n");
	for(int i = 0; i < gui->textNum; i++){
		if(debug){
			printf("Printing index %i\n", i);
			printf("Printing textPos.x %f\n", gui->textPositions[i].x);
			printf("%s\n", gui->texts[i]);
		}
		DrawText(gui->texts[i], gui->textPositions[i].x, gui->textPositions[i].y, gui->textSizes[i], gui->textColors[i]);
		if(debug) printf("Hello? again\n");
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

void gui_renderAnimations(GuiManager * gui, bool debug){
	if(debug){
		// We are in level 1
		printf("anim upf %i\n", gui->animNum);
	}
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

void gui_free(GuiManager gui){
	// Free array of text pointers
	free(gui.texts);
	// Free array of text positions, sizes and colors
	free(gui.textPositions);
	free(gui.textSizes);
	free(gui.textColors);
	// Free array of animations and their positions
	free(gui.animations);
	free(gui.animPositions);	
}

GuiManager gui_alloc(int textNum, int animNum){
	GuiManager gui;
	// Allocate all arrays used for texts
	gui.texts = (const char **) malloc(sizeof(const char *)*textNum);
	gui.textPositions = (Vector2 *) malloc(sizeof(Vector2) * textNum);
	gui.textSizes = (int *) malloc(sizeof(int) * textNum);
	gui.textColors = (Color *) malloc(sizeof(Color) * textNum);
	gui.animations = (Animation *) malloc(sizeof(Animation) * animNum);
	gui.animPositions = (Vector2 *) malloc(sizeof(Vector2) * animNum);
	// Append the values
	gui.textNum = textNum;
	gui.animNum = animNum;
	return gui;
}
