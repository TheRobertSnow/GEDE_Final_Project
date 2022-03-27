#include "pch.h"
#include "ScaleTool.h"
#include "GameObject.h"

ScaleTool::ScaleTool(SceneNode* x_arrow, SceneNode* y_arrow, SceneNode* z_arrow)
{
	x_arrow = x_arrow;
	y_arrow = y_arrow;
	z_arrow = z_arrow;
}

void ScaleTool::SetVisible(bool x = false, bool y = false, bool z = false)
{
	x_arrow->setVisible(x);
	y_arrow->setVisible(y);
	z_arrow->setVisible(z);
}

void ScaleTool::ShowBoundingBoxes(bool x = false, bool y = false, bool z = false)
{
	x_arrow->showBoundingBox(false);
	y_arrow->showBoundingBox(false);
	z_arrow->showBoundingBox(false);
}

bool ScaleTool::GetShowBoundingBox(String axis)
{
	if (axis == "x") {
		return x_arrow->getShowBoundingBox();
	}
	else if (axis == "y") {
		return y_arrow->getShowBoundingBox();
	}
	else if (axis == "z") {
		return z_arrow->getShowBoundingBox();
	}
}

void ScaleTool::ScaleSelectedEntity(SceneNode* selected_entity, SDL_Point new_pos, SDL_Point old_pos, Ogre::Real delta_time, String axis)
{
	if (ScaleTool::GetShowBoundingBox(axis)) {
		int moveX = new_pos.x - old_pos.x;
		int moveY = old_pos.y - new_pos.y;
		int moveZ = new_pos.y - old_pos.y;
		Vector3 currentScale = selected_entity->getScale();
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
		selected_entity->setScale(currentScale);
	}
}

void ScaleTool::MoveToolToNewEntity(SceneNode* selected_entity)
{
	Vector3 selectedEntityPos = selected_entity->getPosition();
	Vector3 selectedEntityScale = selected_entity->getScale() * 50;
	x_arrow->setPosition(selectedEntityPos.x + 2 + selectedEntityScale.x, selectedEntityPos.y, selectedEntityPos.z);
	y_arrow->setPosition(selectedEntityPos.x, selectedEntityPos.y + 2 + selectedEntityScale.y, selectedEntityPos.z);
	z_arrow->setPosition(selectedEntityPos.x, selectedEntityPos.y, selectedEntityPos.z + 2 + selectedEntityScale.z);
}