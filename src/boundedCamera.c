#include "boundedCamera.h"
#include "collisions.h"

Rectangle targetOnScreen(BoundedCamera * camera, Rectangle target){
	target.x = target.x - camera->camera.target.x;
	target.y = target.y - camera->camera.target.y;
	return target;
}

void boundedCamera_updateCamera(BoundedCamera * camera, Rectangle target, float leftLimit, float rightLimit){
	float offsetX = 0.0;
	// Check collision left
	if(CheckCollisionRecs(targetOnScreen(camera, target), camera->leftBound)){
		offsetX = getCollisionSingleXOffset(camera->leftBound, targetOnScreen(camera, target));
		// Move the camera to the left by offset
		camera->camera.target.x -= offsetX;
	} else if(CheckCollisionRecs(targetOnScreen(camera, target), camera->rightBound)) {
		offsetX = getCollisionSingleXOffset(camera->rightBound, targetOnScreen(camera, target));
		// Move the camera to the right by offset
		camera->camera.target.x += offsetX;
	}
	// Now, if we moved out of bounds, imediately move back
	if(camera->camera.target.x < leftLimit){
		camera->camera.target.x = leftLimit;
	}
	if(camera->camera.target.x + camera->rightBound.x + camera->rightBound.width > rightLimit){
		camera->camera.target.x = rightLimit - camera->rightBound.x - camera->rightBound.width;
	}
}
