#pragma once
#include "GameObject.h"

using namespace Ogre;
using namespace OgreBites;

enum LE_Type
{
	MOVE,
	SCALE,
	ROTATE,
	DELETE,
	STATIC,
};

class LE_Event
{
public:
	// Move and Scale constructor
	LE_Event(Ogre::Vector3 old_vec, Ogre::Vector3 new_vec, LE_Type type);
	// Rotate constructor
	LE_Event(Ogre::Quaternion old_rot, Ogre::Quaternion new_rot, LE_Type type);
	// Delete constructor
	LE_Event(GameObject* src, LE_Type type);

	enum LE_Type type_;
	Ogre::Vector3 old_vec_; // Is pos when delete
	Ogre::Vector3 new_vec_; // Is scale when delete
	Ogre::Quaternion old_rot_;
	Ogre::Quaternion new_rot_;
	bool is_selected_;
	Ogre::String mesh_file_name_;
	String axis_;
	bool is_visible_;
};

