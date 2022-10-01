#include "raylib.h"
#ifdef GAME_ANIMATION
#else
#define GAME_ANIMATION
// Frames in the animations texture are stored HORIZONTALLY,
// i.e. frame 2 for frameWidth 10 and frame height 30 will be
// looked for at Rectangle{20,0,10,30}
typedef struct {
	int numFrames;
	int frameWidth;
	int frameHeight;
	int startFrame;
	Rectangle frame;
	Texture2D texture;
	Vector2 renderSize;
	Color colormask;
	// Index that keeps track of how many render functions were called
	int updates;
	// Number of updates per frame - smaller means faster animation
	int upf;
	// Whether to draw in tiled mode, or in pro mode
	bool drawTiled;
	float tileScale;
} Animation;

Animation animation_CreateAnimation(Texture2D texture, int numFrames, int frameWidth, int frameHeight, int startFrame, int upf, float renderWidth, float renderHeight);

void animation_DrawFrame(Animation anim, int frameIndex, Vector2 position);
void animation_DrawUpdate(Animation * anim, Vector2 position);
#endif
