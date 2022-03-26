#pragma once
#include "pch.h"
#include "RoamingCamera.h"
#include "OgreTrays.h"
#include "GameObject.h"

using namespace Ogre;
using namespace OgreBites;

class LevelEditor : public ApplicationContext, public InputListener
{
public:
	LevelEditor();
	virtual ~LevelEditor() {};
	void setup();
	void setupSceneManager();
	void setupCamera();
	void populateScene();
	bool frameStarted(const Ogre::FrameEvent &evt);
	bool keyPressed(const OgreBites::KeyboardEvent& evt);
	bool mousePressed(const OgreBites::MouseButtonEvent& evt);

	Root* root_;
	SceneManager* scene_manager_;
	SceneNode* camera_node_;
	Camera* camera_;
	RoamingCamera* roaming_camera_;

	Entity* object_entity_;
	SceneNode* object_entity_node_;

	bool object_selected_ = false;

	Entity* x_arrow_entity_;
	SceneNode* x_arrow_entity_node_;
	Entity* y_arrow_entity_;
	SceneNode* y_arrow_entity_node_;
	Entity* z_arrow_entity_;
	SceneNode* z_arrow_entity_node_;
};
