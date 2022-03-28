#include "pch.h"
#include "RotateTool.h"
#include "GameObject.h"

RotateTool::RotateTool(SceneNode* x_arrow, SceneNode* y_arrow, SceneNode* z_arrow)
{
	x_arrow_ = x_arrow;
	y_arrow_ = y_arrow;
	z_arrow_ = z_arrow;
}

void RotateTool::SetVisible(bool x = false, bool y = false, bool z = false)
{
	x_arrow_->setVisible(x);
	y_arrow_->setVisible(y);
	z_arrow_->setVisible(z);
}

void RotateTool::ShowBoundingBoxes(bool x = false, bool y = false, bool z = false)
{
	x_arrow_->showBoundingBox(x);
	y_arrow_->showBoundingBox(y);
	z_arrow_->showBoundingBox(z);
}

String RotateTool::GetShowBoundingBox()
{
	if (x_arrow_->getShowBoundingBox()) {
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

void RotateTool::RotateSelectedEntity(SceneNode* selected_entity, SDL_Point new_pos, SDL_Point old_pos, Ogre::Real delta_time, String axis)
{
	if (RotateTool::GetShowBoundingBox() != "") {
		int moveX = old_pos.x - new_pos.x;
		int moveY = new_pos.y - old_pos.y;
		int moveZ = old_pos.y - new_pos.y;
		Quaternion currentRot = selected_entity->getOrientation();
		if (axis == "x") {
			currentRot.x += (moveX * delta_time) * 3;
		}
		else if (axis == "y") {
			currentRot.y += (moveY * delta_time) * 3;
		}
		else if (axis == "z") {
			currentRot.z += (moveZ * delta_time) * 3;
		}
		selected_entity->setOrientation(currentRot);
	}
}

void RotateTool::MoveToolToNewEntity(SceneNode* selected_entity)
{
	Vector3 selectedEntityPos = selected_entity->getPosition();
	x_arrow_->setPosition(selectedEntityPos.x + 4, selectedEntityPos.y, selectedEntityPos.z);
	y_arrow_->setPosition(selectedEntityPos.x, selectedEntityPos.y + 4, selectedEntityPos.z);
	z_arrow_->setPosition(selectedEntityPos.x, selectedEntityPos.y, selectedEntityPos.z + 4);
}