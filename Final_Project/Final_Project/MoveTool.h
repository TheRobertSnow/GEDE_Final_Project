#pragma once
#include "pch.h"

using namespace Ogre;
using namespace OgreBites;

class MoveTool :
{
public:
	MoveTool();
	virtual ~MoveTool() {};

	// move arrows
	Entity* move_x_arrow_entity_;
	SceneNode* move_x_arrow_entity_node_;
	Entity* move_y_arrow_entity_;
	SceneNode* move_y_arrow_entity_node_;
	Entity* move_z_arrow_entity_;
	SceneNode* move_z_arrow_entity_node_;

	// scale arrows
	Entity* scale_x_arrow_entity_;
	SceneNode* scale_x_arrow_entity_node_;
	Entity* scale_y_arrow_entity_;
	SceneNode* scale_y_arrow_entity_node_;
	Entity* scale_z_arrow_entity_;
	SceneNode* scale_z_arrow_entity_node_;
};
