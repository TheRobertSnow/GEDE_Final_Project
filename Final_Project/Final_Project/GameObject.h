#pragma once

using namespace Ogre;
using namespace OgreBites;
class GameObject
{
public:
	GameObject(SceneManager* scene_manager, const char* mesh_file_name,
		Vector3 position, Vector3 scale);
	virtual ~GameObject();

	Entity* entity_;
	SceneNode* scene_node_;
	bool is_selected;
};

