#pragma once
#include "pch.h"
#include "RoamingCamera.h"
#include "OgreTrays.h"
#include "GameObject.h"
#include "MoveTool.h"
#include "ScaleTool.h"
#include "ObjectController.h"
#include "InputManager.h"
#include "RotateTool.h"

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
	void overlayShit();
	void removeSelectedGameObject();
	void duplicateSelectedGameObject();
	void resetTools();
	void setupInputManager();

	bool frameStarted(const Ogre::FrameEvent &evt);
	bool keyPressed(const OgreBites::KeyboardEvent& evt);
	bool mousePressed(const OgreBites::MouseButtonEvent& evt);

	Root* root_;
	SceneManager* scene_manager_;
	InputManager* input_manager_;
	SceneNode* camera_node_;
	Camera* camera_;
	RoamingCamera* roaming_camera_;
	std::list<GameObject*> game_object_list_;

	MoveTool* move_tool_;
	std::list<GameObject*> move_tool_list_;
	ScaleTool* scale_tool_;
	std::list<GameObject*> scale_tool_list_;
	RotateTool* rotate_tool_;
	std::list<GameObject*> rotate_tool_list_;

	GameObject* selected_object_;

	bool object_selected_ = false;
	SDL_Point mousePos;
	bool leftClickPressed = false;
	bool mPressed = false;
	bool sPressed = false;
	bool rPressed = false;
	bool d_pressed_ = false;

	Ogre::OverlayContainer* panel_;
	Ogre::Overlay* overlay_;
	Ogre::TextAreaOverlayElement* text;
};
