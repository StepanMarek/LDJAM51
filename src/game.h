#include "raylib.h"
#include "animation.h"
#ifndef GAME_GAME
#define GAME_GAME
typedef enum {
	PRELUDE,
	MENU,
	LEVEL_PRELUDE,
	LEVEL_PLAY,
	LEVEL_REQUIEM,
	REQUIEM
} GameState;

typedef struct {
	GameState state;
	int textureNum;
	// Expect these on stack
	const char ** textureNames;
	Texture2D * textures;
} Game;

void game_loadTextures(const char ** textureNames, int textureNum, Texture2D * textures);
void game_unloadTextures(Texture2D * textures, int textureNum);
#endif
