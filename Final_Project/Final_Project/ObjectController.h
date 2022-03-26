#pragma once
#include "pch.h"
using namespace Ogre;
using namespace OgreBites;

class ObjectController
{
public:
	ObjectController();
	virtual ~ObjectController() {};
	void MoveEntity(SceneNode* object_entity_node_, SDL_Point new_pos, SDL_Point old_pos, Ogre::Real delta_time, String axis);
	void ScaleEntity(SceneNode* object_entity_node_, SDL_Point new_pos, SDL_Point old_pos, Ogre::Real delta_time, String axis);
	void RotateEntity(SceneNode* object_entity_node_, SDL_Point new_pos, SDL_Point old_pos, Ogre::Real delta_time, String axis);
private:
	
};