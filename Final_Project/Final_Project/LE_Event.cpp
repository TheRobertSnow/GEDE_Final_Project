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

LE_Event::LE_Event(GameObject* src, LE_Type type)
{
	switch (type)
	{
	case DELETE:
		type_ = type;
		game_object_ = src;
		break;
	case DUPLICATE:
		std::cout << "creating action event" << std::endl;
		is_selected_ = src->is_selected_;
		mesh_file_name_ = src->entity_->getMesh()->getName();
		old_vec_ = src->scene_node_->getPosition();
		new_vec_ = src->scene_node_->getScale();
		old_rot_ = src->scene_node_->getOrientation();
		axis_ = src->axis_;
		is_visible_ = src->visible_;
		type_ = type;
		game_object_ = src;
		break;
	default:
		break;
	}
}