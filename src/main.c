#include "raylib.h"
#include <emscripten/emscripten.h>
#include <stdio.h>
#include "game.h"

struct toDraw {
	Texture2D texture;
};

struct toDraw drawing;

int frameCount = 0;
int frameIndex = 0;
Rectangle targetFrame = {0, 0, 50, 100};
Vector2 position = {20, 60};

Game game;
game.textureNum = 1;
game.textureNames = {"res/trial_anim.png"};

void UpdateFrame(){
	BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawFPS(20, 20);
		DrawText("Hello jam!", 20, 40, 12, BLACK);
		DrawTextureRec(drawing.texture, targetFrame, position, BLACK);
		frameCount += 1;
		if(frameCount > 30){
			// Swap frames
			frameIndex = (frameIndex + 1) % 2;
			targetFrame.x = 50 * frameIndex;
			frameCount = 0;
			printf("swapping frame to index : %i\n", frameIndex);
		}
	EndDrawing();
}

int main(){
	InitWindow(800,600, "simple example");

	printf("Game output : %s\n", game.textureNames[0]);

	// Load image as texture
	drawing.texture = LoadTexture("res/trial_anim.png");

	emscripten_set_main_loop(UpdateFrame, 0, 1);

	CloseWindow();

	return 0;
}
