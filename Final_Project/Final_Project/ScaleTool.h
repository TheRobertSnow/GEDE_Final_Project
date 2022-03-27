#pragma once
#include "pch.h"
#include "GameObject.h"

using namespace Ogre;

class ScaleTool
{
public:
	ScaleTool(SceneNode* x_arrow, SceneNode* y_arrow, SceneNode* z_arrow);
	virtual ~ScaleTool() {};
	void SetVisible(bool x, bool y, bool z);
	void ShowBoundingBoxes(bool x, bool y, bool z);
	bool GetShowBoundingBox(String axis);
	void ScaleSelectedEntity(SceneNode* selected_entity, SDL_Point new_pos, SDL_Point old_pos, Ogre::Real delta_time, String axis);
	void MoveToolToNewEntity(SceneNode* selected_entity);

	SceneNode* x_arrow;
	SceneNode* y_arrow;
	SceneNode* z_arrow;
};