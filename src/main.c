#include "raylib.h"
#include <emscripten/emscripten.h>
#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "collisions.h"

Game game;
Vector2 vel = {0.0f, 0.0f};
Vector2 vel2 = {-0.4f, 0.0f};
Rectangle wall = {400,10,20,60};
Rectangle platform = {20, 40, 300, 40};

// Vector2 getCollisionOffset(Vector2 velocity, Rectangle collisionRect){
// 	float offsetScale;
// 	if(fabsf(velocity.x) > fabsf(velocity.y)){
// 		// Width will dominate the offset
// 		offsetScale = collisionRect.width;
// 	} else {
// 		// Height will dominate the offset
// 		offsetScale = collisionRect.height;
// 	}
// 	Vector2 offset = {0,0};
// 	float velocityMag = sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
// 	offset.x = (-velocity.x/velocityMag) * offsetScale;
// 	offset.y = (-velocity.y/velocityMag) * offsetScale;
// 	return offset;
// }

void UpdateFrame(){
	if(IsKeyDown(KEY_D)){
		vel.x = 0.3f;
	} else if(IsKeyDown(KEY_A)){
		vel.x = -0.3f;
	} else {
		vel.x = 0.0f;
	}
	platform.x += vel.x;
	wall.x += vel2.x;
	// Check for collisions
	if(CheckCollisionRecs(platform, wall)){
		handleCollision(&platform, &wall, &vel, &vel2, true, true);
	}
	BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawFPS(20, 20);
		DrawRectangleRec(wall, RED);
		DrawTextureTiled(game.textures[1], (Rectangle){0,0,40,20}, platform, (Vector2){0,0}, 0.0f, 2.0f, WHITE);
	EndDrawing();
}

int main(){
	InitWindow(800,600, "simple example");

	GameState state = PRELUDE;
	// ================= CREATE TEXTURES =================
	const int TEXTURE_NUM = 2;
	const char * textureNames[TEXTURE_NUM];
	game.textureNames = textureNames;
	// Follows loading of textures
	textureNames[0] = "res/trial_anim.png";
	textureNames[1] = "res/platform.png";
	// Create texture pointers on stack
	Texture2D textures[TEXTURE_NUM];
	game.textures = textures;
	game_loadTextures(game.textureNames, TEXTURE_NUM, game.textures);
	// ================= CREATE ANIMATIONS =================
	const int ANIM_NUM = 1;
	Animation animations[ANIM_NUM];
	game.animations = animations;
	game.animations[0] = animation_CreateAnimation(game.textures[0], 2, 50, 100, 0, 20);

	emscripten_set_main_loop(UpdateFrame, 0, 1);

	// Unload
	game_unloadTextures(game.textures, TEXTURE_NUM);

	CloseWindow();

	return 0;
}
