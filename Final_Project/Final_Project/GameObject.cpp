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

void GameObject::RotateObject(Quaternion q, SceneNode* newNode) {
	// roll (x-axis rotation)
	double sinr_cosp = 2 * (q.w * q.x + q.y * q.z);
	double cosr_cosp = 1 - 2 * (q.x * q.x + q.y * q.y);
	newNode->roll(Ogre::Degree(std::atan2(sinr_cosp, cosr_cosp)));

	// pitch (y-axis rotation)
	double sinp = 2 * (q.w * q.y - q.z * q.x);
	if (std::abs(sinp) >= 1)
		newNode->pitch(Ogre::Degree(std::copysign(M_PI / 2, sinp)));
	else
		newNode->pitch(Ogre::Degree(std::asin(sinp)));

	// yaw (z-axis rotation)
	double siny_cosp = 2 * (q.w * q.z + q.x * q.y);
	double cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z);
	newNode->yaw(Ogre::Degree(std::atan2(siny_cosp, cosy_cosp)));
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
