#include "raylib.h"

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
