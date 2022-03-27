#include "pch.h"
#include "GameObject.h"

GameObject::GameObject(SceneManager* scene_manager, const char* mesh_file_name,
	Vector3 position, Vector3 scale)
{
	is_selected_ = false;
	scene_manager_ = scene_manager;
	entity_ = scene_manager_->createEntity(mesh_file_name);
	scene_node_ = scene_manager_->getRootSceneNode()->createChildSceneNode();
	scene_node_->attachObject(entity_);
	scene_node_->setPosition(position);
	scene_node_->setScale(scale);
	entity_->setCastShadows(true);
}

GameObject::~GameObject()
{

}

void GameObject::setSelected(bool val)
{
	is_selected_ = val;
	scene_node_->showBoundingBox(is_selected_);
}
