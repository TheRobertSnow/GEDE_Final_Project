#pragma once
#include "pch.h"
#include "RoamingCamera.h"
#include "OgreTrays.h"
#include "GameObject.h"
//#include "ObjectController.h"
#include "MoveTool.h"
#include "ScaleTool.h"

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
	//void setupObjectController();
	void populateScene();
	void removeSelectedGameObject();
	void duplicateSelectedGameObject();

	bool frameStarted(const Ogre::FrameEvent &evt);
	bool keyPressed(const OgreBites::KeyboardEvent& evt);
	bool mousePressed(const OgreBites::MouseButtonEvent& evt);

	Root* root_;
	SceneManager* scene_manager_;
	SceneNode* camera_node_;
	Camera* camera_;
	RoamingCamera* roaming_camera_;
	//ObjectController* object_controller_;
	std::list<GameObject*> game_object_list_;

	MoveTool* move_tool_;
	std::list<GameObject*> move_tool_list_;
	ScaleTool* scale_tool_;
	std::list<GameObject*> scale_tool_list_;

	GameObject* selected_object_;

	bool object_selected_ = false;
	SDL_Point mousePos;
	bool leftClickPressed = false;
	bool xPressed = false;
	bool yPressed = false;
	bool zPressed = false;
	/*
	bool gPressed = false;
	bool hPressed = false;
	bool jPressed = false;
	bool uPressed = false;
	bool iPressed = false;
	bool oPressed = false;
	*/
	// move arrows
	/*
	Entity* move_x_arrow_entity_;
	SceneNode* move_x_arrow_entity_node_;
	Entity* move_y_arrow_entity_;
	SceneNode* move_y_arrow_entity_node_;
	Entity* move_z_arrow_entity_;
	SceneNode* move_z_arrow_entity_node_;

	// scale arrows
	Entity* scale_x_arrow_entity_;
	SceneNode* scale_x_arrow_entity_node_;
	Entity* scale_y_arrow_entity_;
	SceneNode* scale_y_arrow_entity_node_;
	Entity* scale_z_arrow_entity_;
	SceneNode* scale_z_arrow_entity_node_;
	*/
};
