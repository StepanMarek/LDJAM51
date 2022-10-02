#include "level.h"
#include "gui.h"
#include "game.h"
#include "raylib.h"

Level level_zero(Game game){
	// ================= CREATE ZERO LEVEL =================
	Level level_zero = level_alloc(0, 0, 2, 0, 1, 0);
	// === Create first prelude screen
	gui_constructText(&(level_zero.gui), game.texts[1], 0);
	// Make the text centered
	level_zero.gui.textPositions[0].x = 400;
	level_zero.gui.textPositions[0].y = 300;
	gui_centerText(&(level_zero.gui), 0);
	level_zero.preludeGuis[0] = level_zero.gui;
	level_zero.preludeIndex = 0;
	// ==== Create second prelude screen
	level_zero.preludeGuis[1] = gui_alloc(1, 0);
	gui_constructText(&(level_zero.preludeGuis[1]), game.texts[2], 0);
	level_zero.preludeGuis[1].textPositions[0].x = 400;
	level_zero.preludeGuis[1].textPositions[0].y = 300;
	gui_centerText(&(level_zero.preludeGuis[1]), 0);
	// ==== Create state setup
	level_zero.preludeDone = false;
	level_zero.playDone = true;
	level_zero.requiemDone = false;
	return level_zero;
}
