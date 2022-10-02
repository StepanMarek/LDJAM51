#include "raylib.h"
#include "animation.h"
#include "gui.h"
#ifndef GAME_LEVEL
#define GAME_LEVEL

typedef struct {
	int * keys;
	int * vals;
} IntIntMap;

typedef struct {
	Animation * animations;
	int animNum;
	Vector2 * animPositions;
	int playerAnimIndex;
	Vector2 playerVelocity;
	Rectangle leftBound;
	Rectangle rightBound;
	// Camera is allowed to move slightly out of the level
	float boundOverextension;
	Rectangle * collidingRects;
	Vector2 * collidingVels;
	bool * moveable;
	int collNum;
	IntIntMap collAnimMap;
	// Collisions and damage taking
	int playerCollIndex;
	int * enemies;
	bool * enemiesAlive;
	int enemiesNum;
	int playerHealth;
	//Flare
	int flareTimer;
	bool flaring;
	int flareCooldown;
	int flareDuration;
	int flareAnimIndex;
	// Shielding platform indices
	int * shieldingPlatforms;
	int shieldingPlatformsNum;
	// GUI
	GuiManager gui;
	// This is the gui that is displayed during play
	bool preludeDone;
	bool playDone;
	bool requiemDone;
	int preludeIndex;
	int preludeNum;
	GuiManager * preludeGuis;
	int playNum;
	GuiManager * playGuis;
} Level;

int level_map(Level level, int key);

void level_renderAnimations(Level * level);
void level_handleBoundsCollisions(Level * level);
void level_handleCollisions(Level * level);
void level_updateAnimPositions(Level * level);
void level_progressPrelude(Level * level);
void level_free(Level level);
Level level_alloc(int animNum, int collNum, int preludeNum, int playNum, int guiTextNum, int guiAnimNum, int enemiesNum, int shieldingPlatforms);
void level_takeDamageFromEnemies(Level * level);
void level_updateFlare(Level * level);
#endif
