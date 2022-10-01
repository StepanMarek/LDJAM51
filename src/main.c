#include "raylib.h"
#include <emscripten/emscripten.h>
#include <stdio.h>
#include <stdlib.h>
#include "game.h"

Game game;
int frames;

void UpdateFrame(){
	frames += 1;
	BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawFPS(20, 20);
		DrawText("Hello jam!", 20, 40, 12, BLACK);
		// animation_DrawFrame(anims[0], 0, (Vector2){20,60}, BLACK);
		Vector2 position = {20, 60};
		Vector2 position2 = {20, 200};
		animation_DrawUpdate(game.animations[0], position, BLACK, &(game.animations[0].updates));
		animation_DrawUpdate(game.animations[1], position2, BLACK, &(game.animations[1].updates));
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
	// Create animations
	Animation animations[2];
	game.animations = animations;
	game.animations[0] = animation_CreateAnimation(game.textures[0], 2, 50, 100, 0, 20);
	game.animations[1] = animation_CreateAnimation(game.textures[0], 2, 50, 100, 0, 10);

	emscripten_set_main_loop(UpdateFrame, 0, 1);

	// Unload
	game_unloadTextures(game.textures, TEXTURE_NUM);

	CloseWindow();

	return 0;
}
