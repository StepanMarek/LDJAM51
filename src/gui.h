#include "raylib.h"
#include "animation.h"
#ifndef GAME_GUI
#define GAME_GUI
typedef struct {
	const char ** texts;
	int textNum;
	Vector2 * textPositions;
	int * textSizes;
	Color * textColors;
	Animation * animations;
	Vector2 * animPositions;
	int animNum;
} GuiManager;

void gui_renderTexts(GuiManager * gui, bool debug);

void gui_constructTextWithParams(GuiManager * gui, const char * text, int textIndex, Vector2 textPosition, int textSize, Color textColor);

void gui_constructText(GuiManager * gui, const char * text, int textIndex);

void gui_renderAnimations(GuiManager * gui, bool debug);

void gui_constructAnimationWithParams(GuiManager * gui, int animIndex, Texture2D texture, int numFrames, int frameWidth, int frameHeight, int startFrame, int upf, float renderWidth, float renderHeight);

void gui_constructAnimationStatic(GuiManager * gui, int animIndex, Texture2D texture, int frameWidth, int frameHeight, int frameIndex, float renderWidth, float renderHeight);

void gui_free(GuiManager gui);

GuiManager gui_alloc(int textNum, int animNum);

void gui_centerText(GuiManager * gui, int textIndex);
#endif
