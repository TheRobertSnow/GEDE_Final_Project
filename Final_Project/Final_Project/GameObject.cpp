#include "pch.h"
#include "GameObject.h"

GameObject::GameObject(SceneManager* scene_manager, const char* mesh_file_name,
	Vector3 position, Vector3 scale)
{
	std::cout << "Hello, i exist now!" << std::endl;
	is_selected_ = false;
	scene_manager_ = scene_manager;
	entity_ = scene_manager_->createEntity(mesh_file_name);
	scene_node_ = scene_manager_->getRootSceneNode()->createChildSceneNode();
	scene_node_->attachObject(entity_);
	scene_node_->setPosition(position);
	scene_node_->setScale(scale);
	entity_->setCastShadows(true);
}

// Duplication constructor
GameObject::GameObject(GameObject* src)
{
	is_selected_ = src->is_selected_;
	scene_manager_ = src->scene_manager_;
	entity_ = scene_manager_->createEntity(src->entity_->getMesh()->getName());
	scene_node_ = scene_manager_->getRootSceneNode()->createChildSceneNode();
	scene_node_->attachObject(entity_);
	scene_node_->setPosition(Vector3(3, 1, 3));
	scene_node_->setScale(src->scene_node_->getScale());
	entity_->setCastShadows(true);
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
