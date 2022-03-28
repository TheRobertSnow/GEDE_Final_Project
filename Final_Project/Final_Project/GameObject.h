#pragma once

using namespace Ogre;
using namespace OgreBites;
class GameObject
{
public:
	GameObject(GameObject* src);
	GameObject(SceneManager* scene_manager, const char* mesh_file_name,
		Vector3 position, Vector3 scale, bool castShadows,
		bool visible, int yawAngle, int pitchAngle, String axis);
	GameObject(SceneManager* scene_manager, Ogre::String mesh_file_name,
		Vector3 position, Vector3 scale, bool castShadows,
		bool visible, Ogre::Quaternion rot, String axis);
	virtual ~GameObject();
	void setSelected(bool val);

	SceneManager* scene_manager_;
	Entity* entity_;
	SceneNode* scene_node_;
	bool is_selected_;
	String axis_;
	bool visible_;
};

