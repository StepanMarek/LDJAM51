#include "raylib.h"
#include "animation.h"
#include "level.h"
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
	Level currentLevel;
	Level nextLevel;
	Level * levels;
	int levelIndex;
	int levelNum;
	const char ** texts;
	int textNum;
} Game;

void game_loadTextures(const char ** textureNames, int textureNum, Texture2D * textures);
void game_unloadTextures(Texture2D * textures, int textureNum);
void game_nextLevel(Game * game);
#endif
