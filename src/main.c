#include "raylib.h"
#include <emscripten/emscripten.h>
#include <stdio.h>
#include <stdlib.h>
#include "game.h"

int frameCount = 0;
int frameIndex = 0;
Rectangle targetFrame = {0, 0, 50, 100};
Vector2 position = {20, 60};

Game game;

void UpdateFrame(){
	BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawFPS(20, 20);
		DrawText("Hello jam!", 20, 40, 12, BLACK);
		DrawTextureRec(game.textures[0], targetFrame, position, BLACK);
		frameCount += 1;
		if(frameCount > 30){
			// Swap frames
			frameIndex = (frameIndex + 1) % 2;
			targetFrame.x = 50 * frameIndex;
			frameCount = 0;
		}
	EndDrawing();
}

int main(){
	InitWindow(800,600, "simple example");

	GameState state = PRELUDE;
	
	const int TEXTURE_NUM = 1;
	const char * textureNames[TEXTURE_NUM];
	game.textureNames = textureNames;
	// Follows loading of textures
	textureNames[0] = "res/trial_anim.png";
	// Create texture pointers on stack
	Texture2D textures[TEXTURE_NUM];
	game.textures = textures;
	game_loadTextures(game.textureNames, TEXTURE_NUM, game.textures);

	emscripten_set_main_loop(UpdateFrame, 0, 1);

	// Unload
	game_unloadTextures(game.textures, TEXTURE_NUM);

	CloseWindow();

	return 0;
}
