#include "pch.h"
#include "GameObject.h"

GameObject::GameObject(SceneManager* scene_manager, const char* mesh_file_name,
	Vector3 position, Vector3 scale, bool castShadows = true,
	bool visible = true, int yawAngle = 0, int pitchAngle = 0, String axis = "")
{
	std::cout << "Hello, i exist now!" << std::endl;
	is_selected_ = false;
	scene_manager_ = scene_manager;
	entity_ = scene_manager_->createEntity(mesh_file_name);
	scene_node_ = scene_manager_->getRootSceneNode()->createChildSceneNode();
	scene_node_->attachObject(entity_);
	scene_node_->setPosition(position);
	scene_node_->setScale(scale);
	entity_->setCastShadows(castShadows);
	scene_node_->setVisible(visible);
	scene_node_->yaw(Ogre::Degree(yawAngle));
	scene_node_->pitch(Ogre::Degree(pitchAngle));
	axis_ = axis;
	visible_ = visible;

}

// Duplication constructor
GameObject::GameObject(GameObject* src)
{
	is_selected_ = src->is_selected_;
	scene_manager_ = src->scene_manager_;
	entity_ = scene_manager_->createEntity(src->entity_->getMesh()->getName());
	scene_node_ = scene_manager_->getRootSceneNode()->createChildSceneNode();
	scene_node_->attachObject(entity_);
	scene_node_->setPosition(src->scene_node_->getPosition());
	scene_node_->setScale(src->scene_node_->getScale());
	scene_node_->setVisible(src->visible_);
	scene_node_->setOrientation(src->scene_node_->getOrientation());
	axis_ = src->axis_;
}

GameObject::GameObject(SceneManager* scene_manager, Ogre::String mesh_file_name,
	Vector3 position, Vector3 scale, bool castShadows,
	bool visible, Ogre::Quaternion rot, String axis)
{
	is_selected_ = true;
	scene_manager_ = scene_manager;
	entity_ = scene_manager_->createEntity(mesh_file_name);
	scene_node_ = scene_manager_->getRootSceneNode()->createChildSceneNode();
	scene_node_->attachObject(entity_);
	scene_node_->setPosition(position);
	scene_node_->setScale(scale);
	scene_node_->setVisible(visible);
	scene_node_->setOrientation(rot);
	scene_node_->setVisible(true);
	axis_ = axis;
}

GameObject::~GameObject()
{
	std::cout << "Ok, guess I'll kill myself!" << std::endl;
	scene_node_->removeAndDestroyAllChildren();
	scene_manager_->destroyEntity(entity_);
	scene_manager_->destroySceneNode(scene_node_);
}

void GameObject::setSelected(bool val)
{
	is_selected_ = val;
	scene_node_->showBoundingBox(is_selected_);
}
