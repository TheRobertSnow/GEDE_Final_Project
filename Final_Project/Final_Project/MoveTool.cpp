#include "pch.h"
#include "MoveTool.h"
#include "GameObject.h"

MoveTool::MoveTool(SceneNode* x_arrow, SceneNode* y_arrow, SceneNode* z_arrow)
{
	x_arrow = x_arrow;
	y_arrow = y_arrow;
	z_arrow = z_arrow;
}

void MoveTool::SetVisible(bool x = false, bool y = false, bool z = false)
{
	x_arrow->setVisible(x);
	y_arrow->setVisible(y);
	z_arrow->setVisible(z);
}

void MoveTool::ShowBoundingBoxes(bool x = false, bool y = false, bool z = false)
{
	x_arrow->showBoundingBox(false);
	y_arrow->showBoundingBox(false);
	z_arrow->showBoundingBox(false);
}

bool MoveTool::GetShowBoundingBox(String axis)
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

void MoveTool::MoveSelectedEntity(SceneNode* selected_entity, SDL_Point new_pos, SDL_Point old_pos, Ogre::Real delta_time, String axis)
{
	if (MoveTool::GetShowBoundingBox(axis)) {
		int moveX = new_pos.x - old_pos.x;
		int moveY = old_pos.y - new_pos.y;
		int moveZ = new_pos.y - old_pos.y;
		Vector3 selectedEntityPos = selected_entity->getPosition();
		Vector3 selectedEntityScale = selected_entity->getScale() * 50;
		if (axis == "x") {
			selectedEntityPos.x += (moveX * delta_time) * 15;
		}
		else if (axis == "y") {
			selectedEntityPos.y += (moveY * delta_time) * 15;
		}
		else if (axis == "z") {
			selectedEntityPos.z += (moveZ * delta_time) * 15;
		}
		selected_entity->setPosition(selectedEntityPos);

		// Also move tool with entity :)
		x_arrow->setPosition(selectedEntityPos.x + 2 + selectedEntityScale.x, selectedEntityPos.y, selectedEntityPos.z);
		y_arrow->setPosition(selectedEntityPos.x, selectedEntityPos.y + 2 + selectedEntityScale.y, selectedEntityPos.z);
		z_arrow->setPosition(selectedEntityPos.x, selectedEntityPos.y, selectedEntityPos.z + 2 + selectedEntityScale.z);
	}
}

void MoveTool::MoveToolToNewEntity(SceneNode* selected_entity)
{
	Vector3 selectedEntityPos = selected_entity->getPosition();
	Vector3 selectedEntityScale = selected_entity->getScale() * 50;
	x_arrow->setPosition(selectedEntityPos.x + 2 + selectedEntityScale.x, selectedEntityPos.y, selectedEntityPos.z);
	y_arrow->setPosition(selectedEntityPos.x, selectedEntityPos.y + 2 + selectedEntityScale.y, selectedEntityPos.z);
	z_arrow->setPosition(selectedEntityPos.x, selectedEntityPos.y, selectedEntityPos.z + 2 + selectedEntityScale.z);
}