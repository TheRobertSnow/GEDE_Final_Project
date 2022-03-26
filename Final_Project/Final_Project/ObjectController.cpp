#include "pch.h"
#include "ObjectController.h"

ObjectController::ObjectController()
{
}

void ObjectController::MoveEntity(SceneNode* object_entity_node_, SDL_Point new_pos, SDL_Point old_pos, Ogre::Real delta_time, String axis)
{
		int moveX = new_pos.x - old_pos.x;
		int moveY = old_pos.y - new_pos.y;
		int moveZ = new_pos.y - old_pos.y;
		Vector3 currentPos = object_entity_node_->getPosition();
		if (axis == "x") {
			currentPos.x += (moveX * 20 * delta_time);
		}
		else if (axis == "y") {
			currentPos.y += (moveY * 20 * delta_time);
			if (currentPos.y < 0) {
				currentPos.y = 0;
			}
		}
		else if (axis == "z") {
			currentPos.z += (moveZ * 20 * delta_time);
		}
		object_entity_node_->setPosition(currentPos);
}

void ObjectController::ScaleEntity(SceneNode* object_entity_node_, SDL_Point new_pos, SDL_Point old_pos, Ogre::Real delta_time, String axis)
{
	int moveX = new_pos.x - old_pos.x;
	int moveY = old_pos.y - new_pos.y;
	int moveZ = new_pos.y - old_pos.y;
	Vector3 currentScale = object_entity_node_->getScale();
	if (axis == "x") {
		currentScale.x += ((moveX / 3) * delta_time);
		if (currentScale.x < 0.001) {
			currentScale.x = 0.001;
		}
	}
	else if (axis == "y") {
		currentScale.y += ((moveY / 3) * delta_time);
		if (currentScale.y < 0.001) {
			currentScale.y = 0.001;
		}
	}
	else if (axis == "z") {
		currentScale.z += ((moveZ / 3) * delta_time);
		if (currentScale.z < 0.001) {
			currentScale.z = 0.001;
		}
	}
	object_entity_node_->setScale(currentScale);
}
