#include "pch.h"
#include "ScaleTool.h"
#include "GameObject.h"

ScaleTool::ScaleTool(SceneNode* x_arrow, SceneNode* y_arrow, SceneNode* z_arrow)
{
	x_arrow_ = x_arrow;
	y_arrow_ = y_arrow;
	z_arrow_ = z_arrow;
}

void ScaleTool::SetVisible(bool x = false, bool y = false, bool z = false)
{
	x_arrow_->setVisible(x);
	y_arrow_->setVisible(y);
	z_arrow_->setVisible(z);
}

void ScaleTool::ShowBoundingBoxes(bool x = false, bool y = false, bool z = false)
{
	x_arrow_->showBoundingBox(x);
	y_arrow_->showBoundingBox(y);
	z_arrow_->showBoundingBox(z);
}

String ScaleTool::GetShowBoundingBox()
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

void ScaleTool::ScaleSelectedEntity(SceneNode* selected_entity, SDL_Point new_pos, SDL_Point old_pos, Ogre::Real delta_time, String axis)
{
	if (ScaleTool::GetShowBoundingBox() != "") {
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
	x_arrow_->setPosition(selectedEntityPos.x + 2, selectedEntityPos.y, selectedEntityPos.z);
	y_arrow_->setPosition(selectedEntityPos.x, selectedEntityPos.y + 2, selectedEntityPos.z);
	z_arrow_->setPosition(selectedEntityPos.x, selectedEntityPos.y, selectedEntityPos.z + 2);
}