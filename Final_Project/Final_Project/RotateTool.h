#pragma once
#include "pch.h"
#include "GameObject.h"

using namespace Ogre;

class RotateTool
{
public:
	RotateTool(SceneNode* x_arrow, SceneNode* y_arrow, SceneNode* z_arrow);
	virtual ~RotateTool() {};
	void SetVisible(bool x, bool y, bool z);
	void ShowBoundingBoxes(bool x, bool y, bool z);
	String GetShowBoundingBox();
	void RotateSelectedEntity(SceneNode* selected_entity, SDL_Point new_pos, SDL_Point old_pos, Ogre::Real delta_time, String axis);
	void MoveToolToNewEntity(SceneNode* selected_entity);

	SceneNode* x_arrow_;
	SceneNode* y_arrow_;
	SceneNode* z_arrow_;
};