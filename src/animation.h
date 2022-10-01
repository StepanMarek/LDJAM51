#include "raylib.h"
// Frames in the animations texture are stored HORIZONTALLY,
// i.e. frame 2 for frameWidth 10 and frame height 30 will be
// looked for at Rectangle{20,0,10,30}
typedef struct Animations {
	int numFrames;
	int frameWidth;
	int frameHeight;
	int startFrame;
	Rectangle frame;
	Texture2D texture;
	// Index that keeps track of how many render functions were called
	int updates;
	int * pUpdates;
	// Number of updates per frame - smaller means faster animation
	int upf;
} Animation;

Animation animation_CreateAnimation(Texture2D texture, int numFrames, int frameWidth, int frameHeight, int startFrame, int upf);

void animation_DrawFrame(Animation anim, int frameIndex, Vector2 position, Color color);
void animation_DrawUpdate(Animation anim, Vector2 position, Color color, int * pUpdates);
