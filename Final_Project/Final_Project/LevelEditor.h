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
#include "LE_Event.h"

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
	void removeSelectedGameObject();
	void duplicateSelectedGameObject();
	void resetTools();
	void setupInputManager();
	void moveTools();
	void undoLastAction();

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
	std::deque<LE_Event*> action_queue;
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
	bool xPressed = false;
	bool yPressed = false;
	bool zPressed = false;
	bool d_pressed_ = false;
	bool z_pressed_ = false;
	bool l_ctrl_pressed_ = false;

	// Undo stuff
	bool left_click_down = false;
	bool left_click_up = false;
	bool recording_action = false;
	Ogre::Vector3 last_vec;
	Ogre::Quaternion last_rot;
	LE_Type action_type = LE_Type::STATIC;
};
