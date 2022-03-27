#include "pch.h"
#include "MoveTool.h"
#include "GameObject.h"

MoveTool::MoveTool(SceneNode* x_arrow, SceneNode* y_arrow, SceneNode* z_arrow)
{
	x_arrow_ = x_arrow;
	y_arrow_ = y_arrow;
	z_arrow_ = z_arrow;
}

void MoveTool::SetVisible(bool x = false, bool y = false, bool z = false)
{
	x_arrow_->setVisible(x);
	y_arrow_->setVisible(y);
	z_arrow_->setVisible(z);
}

void MoveTool::ShowBoundingBoxes(bool x = false, bool y = false, bool z = false)
{
	x_arrow_->showBoundingBox(x);
	y_arrow_->showBoundingBox(y);
	z_arrow_->showBoundingBox(z);
}

String MoveTool::GetShowBoundingBox()
{
	if (x_arrow_->getShowBoundingBox()){
		return "x";
	}
	else if (y_arrow_->getShowBoundingBox()) {
		return "y";
	}
	else if (z_arrow_->getShowBoundingBox()) {
		return "z";
	}
	return "";
}

void MoveTool::MoveSelectedEntity(SceneNode* selected_entity, SDL_Point new_pos, SDL_Point old_pos, Ogre::Real delta_time, String axis)
{
	if (MoveTool::GetShowBoundingBox() != "") {
		int moveX = new_pos.x - old_pos.x;
		int moveY = old_pos.y - new_pos.y;
		int moveZ = new_pos.y - old_pos.y;
		Vector3 selectedEntityPos = selected_entity->getPosition();
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
		x_arrow_->setPosition(selectedEntityPos.x + 2, selectedEntityPos.y, selectedEntityPos.z);
		y_arrow_->setPosition(selectedEntityPos.x, selectedEntityPos.y + 2, selectedEntityPos.z);
		z_arrow_->setPosition(selectedEntityPos.x, selectedEntityPos.y, selectedEntityPos.z + 2);
	}
}

void MoveTool::MoveToolToNewEntity(SceneNode* selected_entity)
{
	Vector3 selectedEntityPos = selected_entity->getPosition();
	x_arrow_->setPosition(selectedEntityPos.x + 2, selectedEntityPos.y, selectedEntityPos.z);
	y_arrow_->setPosition(selectedEntityPos.x, selectedEntityPos.y + 2, selectedEntityPos.z);
	z_arrow_->setPosition(selectedEntityPos.x, selectedEntityPos.y, selectedEntityPos.z + 2);
}