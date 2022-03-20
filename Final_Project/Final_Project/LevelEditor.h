#pragma once
#include "pch.h"
#include "RoamingCamera.h"
#include "OgreTrays.h"

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
};
