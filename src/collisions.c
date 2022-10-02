#include "raylib.h"
#include "math.h"

// Start with the more general function for two moving objects colliding
// In this case, they both move to restore non-colliding state
// Returns whether the offset occurs in the x direction
bool getCollisionOffsets(Rectangle * rect1, Rectangle * rect2, Vector2 * vel1, Vector2 * vel2, Vector2 * offset1, Vector2 * offset2){
	// Calculate center
	Vector2 center = {rect1->x + rect1->width/2, rect1->y + rect1->height/2};
	// It is sufficient to know how one will move, other will move in opposite direction
	// Determine collision rectangle
	Rectangle collRect = GetCollisionRec(*rect1, *rect2);
	// And its center
	Vector2 centerColl = {collRect.x + collRect.width/2, collRect.y + collRect.height/2};
	int direction = 1;
	float ratio1, ratio2;
	// Determine offset direction
	if(collRect.width > collRect.height){
		// Move in height/y
		// Determine relative directions
		if(center.y < centerColl.y){
			direction = -1;
		}
		// Determine offset ratios
		ratio1 = fabsf(vel1->y) / (fabsf(vel1->y) + fabsf(vel2->y));
		ratio2 = 1-ratio1;
		offset1->x = 0.0;
		offset1->y = direction * (collRect.height * ratio1);
		offset2->x = 0.0;
		offset2->y = - direction * (collRect.height * ratio2);
		return false;
	} else {
		// Move in width/x
		// Determine relative directions
		if(center.x < centerColl.x){
			direction = -1;
		}
		// Determine offset ratios
		ratio1 = fabsf(vel1->x) / (fabsf(vel1->x) + fabsf(vel2->x));
		ratio2 = 1-ratio1;
		offset1->y = 0.0;
		offset1->x = direction * (collRect.width * ratio1);
		offset2->y = 0.0;
		offset2->x = - direction * (collRect.width * ratio2);
		return true;
	}
}

// Similar function, but now only the first rectangle can move
// Therefore, it moves the whole offset
bool getCollisionSingleOffset(Rectangle * rect1, Rectangle * rect2, Vector2 * offset){
	// Calculate center
	Vector2 center = {rect1->x + rect1->width/2, rect1->y + rect1->height/2};
	// It is sufficient to know how one will move, other will move in opposite direction
	// Determine collision rectangle
	Rectangle collRect = GetCollisionRec(*rect1, *rect2);
	// And its center
	Vector2 centerColl = {collRect.x + collRect.width/2, collRect.y + collRect.height/2};
	int direction = 1;
	// Determine offset direction
	if(collRect.width > collRect.height){
		// Move in height/y
		// Determine relative directions
		if(center.y < centerColl.y){
			direction = -1;
		}
		offset->x = 0.0;
		offset->y = direction * collRect.height;
		return false;
	} else {
		// Move in width/x
		// Determine relative directions
		if(center.x < centerColl.x){
			direction = -1;
		}
		offset->y = 0.0;
		offset->x = direction * collRect.width;
		return true;
	}
}

// This is the most general function - handles the collision based on movability
void handleCollision(Rectangle * rect1, Rectangle * rect2, Vector2 * vel1, Vector2 * vel2, bool move1, bool move2){
	bool movedInX;
	// Start by determining the situation
	if(!(move1 && move2)){
		// At least one is immovable
		if(move1){
			// First is mobile
			Vector2 offset = {0.0, 0.0};
			movedInX = getCollisionSingleOffset(rect1, rect2, &offset);
			// Apply offset
			if(movedInX){
				rect1->x += offset.x;
				vel1->x = 0.0;
			} else {
				rect1->y += offset.y;
				vel1->y = 0.0;
			}
		}
		if(move2){
			// Second is mobile
			Vector2 offset = {0.0, 0.0};
			movedInX = getCollisionSingleOffset(rect2, rect1, &offset);
			// Apply offset
			if(movedInX){
				rect2->x += offset.x;
				vel2->x = 0.0;
			} else {
				rect2->y += offset.y;
				vel2->y = 0.0;
			}
		}
		// If neither are mobile, do not move
		return;
	} else {
		// Both are mobile
		Vector2 offset1 = {0.0, 0.0};
		Vector2 offset2 = {0.0, 0.0};
		movedInX = getCollisionOffsets(rect1, rect2, vel1, vel2, &offset1, &offset2);
		if(movedInX){
			rect1->x += offset1.x;
			rect2->x += offset2.x;
			vel1->x = 0.0;
			vel2->x = 0.0;
		} else {
			rect1->y += offset1.y;
			rect2->y += offset2.y;
			vel1->y = 0.0;
			vel2->y = 0.0;
		}
	}
}

float getCollisionSingleXOffset(Rectangle rect1, Rectangle rect2){
	// Returns the overlap in x direction of the two rectangles
	Rectangle collRect = GetCollisionRec(rect1, rect2);
	return collRect.width;
}

void handleSingleXCollision(Rectangle * rect1, Rectangle rect2){
	// Get the offset
	float offsetX = getCollisionSingleXOffset(*rect1, rect2);
	// Depending on direction, move the movable rectangle
	if(rect2.x > rect1->x){
		// Collision from the left, move back left
		rect1->x -= offsetX;
	} else {
		// Collision from the right, move back right
		rect1->x += offsetX;
	}
}

float getCollisionShielded(Rectangle rect1, Rectangle rect2){
	// Returns the overlap in x direction of the two rectangles
	// Even when they are not strictly overlapping
	if(rect1.x > rect2.x){
		if(rect2.x + rect2.width > rect1.x){
			return rect2.x + rect2.width - rect1.x;
		}
		else{
			return 0.0f;
		}
	} else {
		if(rect1.x + rect1.width > rect2.x){
			return rect1.x + rect1.width - rect2.x;
		} else {
			return 0.0f;
		}
	}
}

