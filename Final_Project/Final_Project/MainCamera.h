#pragma once
using namespace Ogre;
using namespace OgreBites;
class MainCamera
{
public:
	MainCamera(SceneManager* scene_manager, RenderWindow*
		render_window, Vector3 position, Vector3 lookat_position);
	virtual~MainCamera();

	SceneManager* scene_manager_;
	SceneNode* camera_node_;
	Camera* camera_;
};

