#pragma once
#include "pch.h"
#include "RoamingCamera.h"
#include "OgreTrays.h"
#include "GameObject.h"
#include "ObjectController.h"

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
	void setupObjectController();
	void populateScene();
	bool frameStarted(const Ogre::FrameEvent &evt);
	bool keyPressed(const OgreBites::KeyboardEvent& evt);
	bool mousePressed(const OgreBites::MouseButtonEvent& evt);

	Root* root_;
	SceneManager* scene_manager_;
	SceneNode* camera_node_;
	Camera* camera_;
	RoamingCamera* roaming_camera_;
	ObjectController* object_controller_;

	Entity* object_entity_;
	SceneNode* object_entity_node_;

	bool object_selected_ = false;
	SDL_Point mousePos;
	bool leftClickPressed = false;
	bool xPressed = false;
	bool yPressed = false;
	bool zPressed = false;
	bool gPressed = false;
	bool hPressed = false;
	bool jPressed = false;
};
