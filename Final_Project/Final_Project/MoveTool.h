#pragma once
#include "pch.h"

using namespace Ogre;

class MoveTool
{
public:
	MoveTool(SceneNode* x_arrow, SceneNode* y_arrow, SceneNode* z_arrow);
	virtual ~MoveTool() {};
	void SetVisible(bool x, bool y, bool z);
	void ShowBoundingBoxes(bool x, bool y, bool z);
	bool GetShowBoundingBox(String axis);
	void MoveSelectedEntity(SceneNode* selected_entity, SDL_Point new_pos, SDL_Point old_pos, Ogre::Real delta_time, String axis);
	void MoveToolToNewEntity(SceneNode* selected_entity);

	SceneNode* x_arrow;
	SceneNode* y_arrow;
	SceneNode* z_arrow;
};
