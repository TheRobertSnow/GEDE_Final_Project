#pragma once

using namespace Ogre;
using namespace OgreBites;
class GameObject
{
public:
	GameObject(SceneManager* scene_manager, const char* mesh_file_name,
		Vector3 position, Vector3 scale, bool castShadows, 
		bool visible, int yawAngle, int pitchAngle);
	virtual ~GameObject();
	void setSelected(bool val);

	SceneManager* scene_manager_;
	Entity* entity_;
	SceneNode* scene_node_;
	bool is_selected_;
};

