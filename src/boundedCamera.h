#include "raylib.h"
#include "collisions.h"

typedef struct {
	Camera2D camera;
	Rectangle leftBound;
	Rectangle rightBound;
} BoundedCamera;

// If the target is within either bound, move the camera so that the
// target is no longer within the bound. But, only do so if the left bound
// itself does not get pushed out of limits (set by level dimensions)
void boundedCamera_updateCamera(BoundedCamera * camera, Rectangle target, float leftLimit, float rightLimit);
