#include "pch.h"
#include "LE_Event.h"


LE_Event::LE_Event(Ogre::Vector3 old_vec, Ogre::Vector3 new_vec, LE_Type type)
{
	old_vec_ = old_vec;
	new_vec_ = new_vec;
	type_ = type;
}

LE_Event::LE_Event(Ogre::Quaternion old_rot, Ogre::Quaternion new_rot, LE_Type type)
{
	old_rot_ = old_rot;
	new_rot_ = new_rot;
	type_ = type;
}