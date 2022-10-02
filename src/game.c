#include "raylib.h"
#include "level.h"
#include "game.h"

void game_loadTextures(const char ** textureNames, int textureNum, Texture2D * textures){
	// Assumes textures is correctly created with required number of slots
	for(int i = 0; i < textureNum; i++){
		textures[i] = LoadTexture(textureNames[i]);
	}
}

void game_unloadTextures(Texture2D * textures, int textureNum){
	// Unloads all textures from memory
	for(int i = 0; i < textureNum; i++){
		UnloadTexture(textures[i]);
	}
}

void game_nextLevel(Game * game){
	game->currentLevel = game->nextLevel;
	game->levelIndex += 1;
	if(game->levelIndex >= game->levelNum){
		// TODO : Loop good default behaviour?
		game->levelIndex = -1;
	}
	game->nextLevel = game->levels[game->levelIndex+1];
}
