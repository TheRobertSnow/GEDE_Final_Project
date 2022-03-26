#include "pch.h"
#include "ObjectController.h"

using namespace std;

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
		currentPos.x += (moveX * delta_time) * 15;
	}
	else if (axis == "y") {
		currentPos.y += (moveY * delta_time) * 15;
	}
	else if (axis == "z") {
		currentPos.z += (moveZ * delta_time) * 15;
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
		currentScale.x += (moveX * delta_time) / 5;
		if (currentScale.x < 0) {
			currentScale.x = 0;
		}
	}
	else if (axis == "y") {
		currentScale.y += (moveY * delta_time) / 5;
		if (currentScale.y < 0) {
			currentScale.y = 0;
		}
	}
	else if (axis == "z") {
		currentScale.z += (moveZ * delta_time) / 5;
		if (currentScale.z < 0) {
			currentScale.z = 0;
		}
	}
	object_entity_node_->setScale(currentScale);
}

void ObjectController::RotateEntity(SceneNode* object_entity_node_, SDL_Point new_pos, SDL_Point old_pos, Ogre::Real delta_time, String axis)
{
	int moveX = new_pos.x - old_pos.x;
	int moveY = old_pos.y - new_pos.y;
	int moveZ = new_pos.y - old_pos.y;
	Quaternion currentRot = object_entity_node_->getOrientation();
	if (axis == "x") {
		currentRot.x += (moveX * delta_time) * 3;
	}
	else if (axis == "y") {
		currentRot.y += (moveY * delta_time) * 3;
	}
	else if (axis == "z") {
		currentRot.z += (moveZ * delta_time) * 3;
	}
	object_entity_node_->setOrientation(currentRot);
}
