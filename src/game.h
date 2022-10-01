enum GameStates {
	PRELUDE,
	MENU,
	LEVEL_PRELUDE,
	LEVEL_PLAY,
	LEVEL_REQUIEM,
	REQUIEM
} GameState;

struct Game {
	GameState state;
	int textureNum;
	const char ** textureNames;	
};
