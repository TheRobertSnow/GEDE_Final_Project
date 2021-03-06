#include "pch.h"
#include "LevelEditor.h"
# include "MoveTool.h"
# include "ScaleTool.h"
# include "RotateTool.h"

using namespace std;

LevelEditor::LevelEditor() : ApplicationContext("Level Editor")
{

}

void LevelEditor::setup()
{
	ApplicationContext::setup();
	addInputListener(this);
	setupSceneManager();
	setupCamera();
	populateScene();
	//overlayShit();
	setupInputManager();
}

void LevelEditor::setupInputManager() 
{
	input_manager_ = new InputManager();
}

void LevelEditor::setupSceneManager()
{
	// Get pointers to root and create scene manager
	root_ = getRoot();
	scene_manager_ = root_->createSceneManager();

	// Register scene with the RTSS
	RTShader::ShaderGenerator* shaderGenerator = RTShader::ShaderGenerator::getSingletonPtr();
	shaderGenerator->addSceneManager(scene_manager_);
}

void LevelEditor::setupCamera()
{
	roaming_camera_ = new RoamingCamera(scene_manager_, getRenderWindow(), Vector3(0, 0, 50));
}

void LevelEditor::populateScene()
{
	// Add Ground
	Plane plane(Ogre::Vector3::UNIT_Y, -5);
	MeshPtr groundMesh = MeshManager::getSingleton()
		.createPlane("MainGround", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
			plane, 1000, 1000, 100, 100, true, 1, 50, 50, Ogre::Vector3::UNIT_Z);

	// build tangent vectors for our mesh, to show the normal texture
		// This will make the floor tiles look like they have depth, even thought they are flat
	unsigned short src, dest;
	if (!groundMesh->suggestTangentVectorBuildParams(VES_TANGENT, src, dest))
	{
		groundMesh->buildTangentVectors(VES_TANGENT, src, dest);
	}

	Entity* groundEntity = scene_manager_->createEntity("LightPlaneEntity", "MainGround");
	scene_manager_->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);
	groundEntity->setCastShadows(false);

	// Specify the material that is going to be used to render the floor tiles
	groundEntity->setMaterialName("Custom/BrickTiles");

	groundEntity->setRenderQueueGroup(1);

	// Set Shadow Technique
	scene_manager_->setShadowTechnique(Ogre::ShadowTechnique::SHADOWTYPE_STENCIL_MODULATIVE);

	// Add Directional Light
	scene_manager_->setAmbientLight(Ogre::ColourValue(0.2f, 0.5f, 0.8f));
	Light* directionalLight = scene_manager_->createLight("DirectionalLight");
	directionalLight->setType(Ogre::Light::LT_DIRECTIONAL);
	directionalLight->setDiffuseColour(1, 1, 1);
	directionalLight->setSpecularColour(.4, .4, .4);
	SceneNode* directionalLightNode = scene_manager_->getRootSceneNode()->createChildSceneNode();
	directionalLightNode->attachObject(directionalLight);
	directionalLightNode->setDirection(Ogre::Vector3(0, -1, -1));

	// Add object to scene
	GameObject* newObj = new GameObject(scene_manager_, "cube.mesh", Vector3(0, 0, 0), Vector3(0.01, 0.01, 0.01), true, true, 0, 0, "");
	game_object_list_.push_back(newObj);
	GameObject* newObj2 = new GameObject(scene_manager_, "cube.mesh", Vector3(2, 0, 0), Vector3(0.01, 0.01, 0.01), true, true, 0, 0, "");
	game_object_list_.push_back(newObj2);

	newObj->entity_->setRenderQueueGroup(2);
	newObj2->entity_->setRenderQueueGroup(2);

	// Move Tool Arrows
	GameObject* movex = new GameObject(scene_manager_, "X_arrow.mesh", Vector3(2, 0, 0), Vector3(1, 1, 1), false, false, 270, 0, "x");
	move_tool_list_.push_back(movex);
	GameObject* movey = new GameObject(scene_manager_, "Y_arrow.mesh", Vector3(0, 2, 0), Vector3(1, 1, 1), false, false, 0, 90, "y");
	move_tool_list_.push_back(movey);
	GameObject* movez = new GameObject(scene_manager_, "Z_arrow.mesh", Vector3(0, 0, 2), Vector3(1, 1, 1), false, false, 180, 0, "z");
	move_tool_list_.push_back(movez);
	move_tool_ = new MoveTool(movex->scene_node_, movey->scene_node_, movez->scene_node_);

	movex->entity_->setRenderQueueGroup(3);
	movey->entity_->setRenderQueueGroup(3);
	movez->entity_->setRenderQueueGroup(3);

	// Scale Tool Arrows
	GameObject* scalex = new GameObject(scene_manager_, "X_cube.mesh", Vector3(2, 0, 0), Vector3(1, 1, 1), false, false, 270, 0, "x");
	scale_tool_list_.push_back(scalex);
	GameObject* scaley = new GameObject(scene_manager_, "Y_cube.mesh", Vector3(0, 2, 0), Vector3(1, 1, 1), false, false, 0, 90, "y");
	scale_tool_list_.push_back(scaley);
	GameObject* scalez = new GameObject(scene_manager_, "Z_cube.mesh", Vector3(0, 0, 2), Vector3(1, 1, 1), false, false, 180, 0, "z");
	scale_tool_list_.push_back(scalez);
	scale_tool_ = new ScaleTool(scalex->scene_node_, scaley->scene_node_, scalez->scene_node_);

	scalex->entity_->setRenderQueueGroup(3);
	scaley->entity_->setRenderQueueGroup(3);
	scalez->entity_->setRenderQueueGroup(3);

	// Rotate Tool Arrows
	GameObject* rotatex = new GameObject(scene_manager_, "X_sphere.mesh", Vector3(4, 0, 0), Vector3(1.5, 1.5, 1.5), false, false, 0, 0, "x");
	rotate_tool_list_.push_back(rotatex);
	GameObject* rotatey = new GameObject(scene_manager_, "Y_sphere.mesh", Vector3(0, 4, 0), Vector3(1.5, 1.5, 1.5), false, false, 0, 0, "y");
	rotate_tool_list_.push_back(rotatey);
	GameObject* rotatez = new GameObject(scene_manager_, "Z_sphere.mesh", Vector3(0, 0, 4), Vector3(1.5, 1.5, 1.5), false, false, 0, 0, "z");
	rotate_tool_list_.push_back(rotatez);
	rotate_tool_ = new RotateTool(rotatex->scene_node_, rotatey->scene_node_, rotatez->scene_node_);

	rotatex->entity_->setRenderQueueGroup(3);
	rotatey->entity_->setRenderQueueGroup(3);
	rotatez->entity_->setRenderQueueGroup(3);
}

bool LevelEditor::frameStarted(const Ogre::FrameEvent& evt)
{
	ApplicationContext::frameStarted(evt);
	// Store the time that has passed since last time we got the callback
	const Ogre::Real delta_time = evt.timeSinceLastFrame;
	// Check what keys of the keyboard are being pressed
	const Uint8* state = SDL_GetKeyboardState(nullptr);
	// Get Mouse Pos each frame
	SDL_Point p;
	const Uint32 mouse_state = SDL_GetMouseState(&p.x, &p.y);

	// Manage new input in input manager
	input_manager_->update(state, &mouse_state);

	// Keyboard stuff
	if (state[SDL_SCANCODE_LCTRL])
	{
		l_ctrl_pressed_ = true;
		if (state[SDL_SCANCODE_D])
		{
			if (!d_pressed_)
			{
				d_pressed_ = true;
				action_type = DUPLICATE;
				if (selected_object_ != nullptr) duplicateSelectedGameObject();
				action_type = STATIC;
			}
		}
		else
		{
			d_pressed_ = false;
		}
		if (state[SDL_SCANCODE_Z])
		{
			if (!z_pressed_)
			{
				z_pressed_ = true;
				if (action_queue.size() > 0) undoLastAction();
			}
		}
		else
		{
			z_pressed_ = false;
		}
	}
	else {
		l_ctrl_pressed_ = false;
	}

	// Mouse stuff
	if (left_click_up) left_click_up = false;
	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(1)) {
		if (!leftClickPressed) {
			left_click_down = true;
			leftClickPressed = true;
		}
		else {
			left_click_down = false;
		}
	}
	else {
		if (leftClickPressed) {
			left_click_up = true;
			leftClickPressed = false;
		}
	}

	// More Mouse stuff
	if (right_click_up) right_click_up = false;
	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(3)) {
		if (!rightClickPressed) {
			rightClickPressed = true;
		}
	}
	else {
		if (rightClickPressed) {
			rightClickPressed = false;
		}
	}

	// update the roaming camera
	if (roaming_camera_ != nullptr) roaming_camera_->update(delta_time, state);


	// Move Button
	if (mPressed) {
		if (selected_object_ == nullptr) {
			mPressed = false;
		}
		else {
			move_tool_->SetVisible(true, true, true); // Show the tool arrows
			if (left_click_down) {
				std::cout << "recording action" << selected_object_->scene_node_->getPosition() << std::endl;
				last_vec = selected_object_->scene_node_->getPosition();
				action_type = LE_Type::MOVE;
			}
		}
	}
	else {
		move_tool_->SetVisible(false, false, false); // Hide the tool arrows
	}

	// Scale Button
	if (sPressed) {
		if (selected_object_ == nullptr) {
			sPressed = false;
		}
		else {
			scale_tool_->SetVisible(true, true, true); // Show the tool arrows
			if (left_click_down) {
				last_vec = selected_object_->scene_node_->getScale();
				action_type = LE_Type::SCALE;
			}
		}
	}
	else {
		scale_tool_->SetVisible(false, false, false); // Hide the tool arrows
	}

	// Rotate Button
	if (rPressed) {
		if (selected_object_ == nullptr) {
			rPressed = false;
		}
		else {
			rotate_tool_->SetVisible(true, true, true); // Show the tool arrows
			if (left_click_down) {
				last_rot = selected_object_->scene_node_->getOrientation();
				action_type = LE_Type::ROTATE;
			}
		}
	}
	else {
		rotate_tool_->SetVisible(false, false, false); // Hide the tool arrows
	}
	if (selected_object_ != nullptr && leftClickPressed) {
		// Move Entities
		move_tool_->MoveSelectedEntity(selected_object_->scene_node_, p, mousePos, delta_time, move_tool_->GetShowBoundingBox());
		// Move Scale Tool to same location as Move tool
		scale_tool_->MoveToolToNewEntity(selected_object_->scene_node_);
		// Scale Entities
		scale_tool_->ScaleSelectedEntity(selected_object_->scene_node_, p, mousePos, delta_time, scale_tool_->GetShowBoundingBox());
		// Move Rotate Tool to same location as Move tool
		rotate_tool_->MoveToolToNewEntity(selected_object_->scene_node_);
		// Rotate Entities
		rotate_tool_->RotateSelectedEntity(selected_object_->scene_node_, p, mousePos, delta_time, rotate_tool_->GetShowBoundingBox());
	}
	else if (left_click_up) {
		std::cout << "Creating action" << std::endl;
		if (action_type == LE_Type::MOVE)
		{
			action_queue.push_back(new LE_Event(selected_object_,last_vec, selected_object_->scene_node_->getPosition(), action_type));
			std::cout << action_queue.back()->old_vec_ << std::endl;
		}
		else if (action_type == LE_Type::ROTATE)
		{
			action_queue.push_back(new LE_Event(selected_object_,last_rot, selected_object_->scene_node_->getOrientation(), action_type));
		}
		else if (action_type == LE_Type::SCALE)
		{
			action_queue.push_back(new LE_Event(selected_object_, last_vec, selected_object_->scene_node_->getScale(), action_type));
		}
		action_type = LE_Type::STATIC;
	}
	mousePos = p;
	return true;
}

bool LevelEditor::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == OgreBites::SDLK_ESCAPE)
	{
		getRoot()->queueEndRendering();
	}
	// m = 109
	else if (evt.keysym.sym == 109)
	{
		if (mPressed) {
			mPressed = false;
		}
		else {
			mPressed = true;
		}
		sPressed = false;
		rPressed = false;
		move_tool_->ShowBoundingBoxes(false, false, false);
		scale_tool_->ShowBoundingBoxes(false, false, false);
		rotate_tool_->ShowBoundingBoxes(false, false, false);
	}
	// s = 115
	else if (evt.keysym.sym == 115)
	{
		// Add check if !rightclickpressed
		if (!rightClickPressed) {
			if (sPressed) {
				sPressed = false;
			}
			else {
				sPressed = true;
			}
			mPressed = false;
			rPressed = false;
			move_tool_->ShowBoundingBoxes(false, false, false);
			scale_tool_->ShowBoundingBoxes(false, false, false);
			rotate_tool_->ShowBoundingBoxes(false, false, false);
		}
	}
	// r = 114
	else if (evt.keysym.sym == 114)
	{
		if (!l_ctrl_pressed_)
		{
			if (rPressed) {
				rPressed = false;
			}
			else {
				rPressed = true;
			}
			mPressed = false;
			sPressed = false;
			move_tool_->ShowBoundingBoxes(false, false, false);
			scale_tool_->ShowBoundingBoxes(false, false, false);
			rotate_tool_->ShowBoundingBoxes(false, false, false);
		}
	}
	else if (evt.keysym.sym == OgreBites::SDLK_DELETE)
	{
		action_type = DELETE;
		removeSelectedGameObject();
		action_type = STATIC;
	}
	return true;
}

bool LevelEditor::mousePressed(const OgreBites::MouseButtonEvent& evt) 
{
	if (evt.type == OgreBites::MOUSEBUTTONDOWN)
	{
		// get window height and width
		Ogre::Real screenWidth = root_->getRenderSystem()->_getViewport()->getActualWidth();
		Ogre::Real screenHeight = root_->getRenderSystem()->_getViewport()->getActualHeight();

		// convert to 0-1 offset
		Ogre::Real offsetX = evt.x / screenWidth;
		Ogre::Real offsetY = evt.y / screenHeight;

		// set up the ray
		Ray mouseRay = roaming_camera_->getCamera()->getCameraToViewportRay(offsetX, offsetY);
		if (evt.button == OgreBites::BUTTON_LEFT)
		{
			std::pair<bool, Ogre::Real> result;
			bool obj_was_selected = false;
			// Loop through list of game objects
			for (auto const& i : game_object_list_) {
				// Test if mouse ray collides with a game object
				result = mouseRay.intersects(i->scene_node_->_getWorldAABB());
				// If ray collides with game object
				if (result.first) 
				{
					// If a game object is already selected
					if (selected_object_ != nullptr)
					{
						selected_object_->setSelected(false);
						selected_object_ = i;
						selected_object_->setSelected(true);
					}
					// If a game object is not selected
					else
					{
						selected_object_ = i;
						selected_object_->setSelected(true);
					}
					// Move all tools to same location as newly selected object
					move_tool_->MoveToolToNewEntity(i->scene_node_);
					scale_tool_->MoveToolToNewEntity(i->scene_node_);
					rotate_tool_->MoveToolToNewEntity(i->scene_node_);
					obj_was_selected = true;
				}
			}
			int move_arrows_clicked_count = 3;
			if (mPressed) {
				std::pair<bool, Ogre::Real> resultMove;
				for (auto const& i : move_tool_list_) {
					resultMove = mouseRay.intersects(i->scene_node_->_getWorldAABB());
					if (resultMove.first)
					{
						if (i->axis_ == "x") {
							move_tool_->ShowBoundingBoxes(true, false, false);
						}
						else if (i->axis_ == "y") {
							move_tool_->ShowBoundingBoxes(false, true, false);
						}
						else if (i->axis_ == "z") {
							move_tool_->ShowBoundingBoxes(false, false, true);
						}
					}
					else {
						move_arrows_clicked_count -= 1;
					}
				}
			}
			int scale_arrows_clicked_count = 3;
			if (sPressed) {
				std::pair<bool, Ogre::Real> resultScale;
				for (auto const& i : scale_tool_list_) {
					resultScale = mouseRay.intersects(i->scene_node_->_getWorldAABB());
					if (resultScale.first)
					{
						if (i->axis_ == "x") {
							scale_tool_->ShowBoundingBoxes(true, false, false);
						}
						else if (i->axis_ == "y") {
							scale_tool_->ShowBoundingBoxes(false, true, false);
						}
						else if (i->axis_ == "z") {
							scale_tool_->ShowBoundingBoxes(false, false, true);
						}
					}
					else {
						scale_arrows_clicked_count -= 1;
					}
				}
			}
			int rotate_arrows_clicked_count = 3;
			if (rPressed) {
				std::pair<bool, Ogre::Real> resultRotate;
				for (auto const& i : rotate_tool_list_) {
					resultRotate = mouseRay.intersects(i->scene_node_->_getWorldAABB());
					if (resultRotate.first)
					{
						if (i->axis_ == "x") {
							rotate_tool_->ShowBoundingBoxes(true, false, false);
						}
						else if (i->axis_ == "y") {
							rotate_tool_->ShowBoundingBoxes(false, true, false);
						}
						else if (i->axis_ == "z") {
							rotate_tool_->ShowBoundingBoxes(false, false, true);
						}
					}
					else {
						rotate_arrows_clicked_count -= 1;
					}
				}
			}
			if (!obj_was_selected) {
				if (selected_object_ != nullptr)
				{
					// Check if two of these are true then some arrow is clicked
					if (move_tool_->GetShowBoundingBox() != "" || scale_tool_->GetShowBoundingBox() != "" || rotate_tool_->GetShowBoundingBox() != "") {
						if (move_arrows_clicked_count == 0 || scale_arrows_clicked_count == 0 || rotate_arrows_clicked_count == 0) {
							// Click outside box and arrow when arrow selected
							// Turn off tool and deselect box
							LevelEditor::resetTools();
							selected_object_->setSelected(false);
							selected_object_ = nullptr;
						}
					}
					else {
						// Click outside box when no tool selected
						// deselect box
						selected_object_->setSelected(false);
						selected_object_ = nullptr;
					}
				}
			}
		}
	}
	return true;
}

void LevelEditor::removeSelectedGameObject()
{
	// Check if any object is seleceted
	if (selected_object_ != nullptr)
	{
		// Start by creating an action event
		action_queue.push_back(new LE_Event(selected_object_, action_type));
		// Destroy the GameObject and remove it from game_object_list_
		delete selected_object_;
		game_object_list_.remove(selected_object_);
		selected_object_ = nullptr;
		// Reset the tools
		LevelEditor::resetTools();
	}
}

void LevelEditor::duplicateSelectedGameObject()
{
	GameObject* duplicateOfObject = new GameObject(selected_object_);
	// Set the duplicate as the selected object
	selected_object_->setSelected(false);
	selected_object_ = duplicateOfObject;
	//selected_object_->setSelected(true);
	// Create action event
	action_queue.push_back(new LE_Event(duplicateOfObject, action_type));
	std::cout << action_queue.size() << endl;

	// Move all tools to same location as new duplicate object
	move_tool_->MoveToolToNewEntity(duplicateOfObject->scene_node_);
	scale_tool_->MoveToolToNewEntity(duplicateOfObject->scene_node_);
	rotate_tool_->MoveToolToNewEntity(duplicateOfObject->scene_node_);
	game_object_list_.push_back(duplicateOfObject);

	// Change active tool to move tool because we can assume the creator wants to move the duplicated object
	mPressed = true;
	sPressed = false;
	rPressed = false;
	move_tool_->ShowBoundingBoxes(false, false, false);
	scale_tool_->ShowBoundingBoxes(false, false, false);
	rotate_tool_->ShowBoundingBoxes(false, false, false);
}

void LevelEditor::resetTools()
{
	mPressed = false;
	move_tool_->SetVisible(false, false, false);
	move_tool_->ShowBoundingBoxes(false, false, false);
	sPressed = false;
	scale_tool_->SetVisible(false, false, false);
	scale_tool_->ShowBoundingBoxes(false, false, false);
	rPressed = false;
	rotate_tool_->SetVisible(false, false, false);
	rotate_tool_->ShowBoundingBoxes(false, false, false);
}

void LevelEditor::moveTools()
{
	if (selected_object_ != nullptr)
	{
		move_tool_->MoveToolToNewEntity(selected_object_->scene_node_);
		scale_tool_->MoveToolToNewEntity(selected_object_->scene_node_);
		rotate_tool_->MoveToolToNewEntity(selected_object_->scene_node_);
	}
}

void LevelEditor::undoLastAction()
{
	std::cout << "Undo last action" << std::endl;
	LE_Event* action = action_queue.back();
	std::cout << action_queue.size() << std::endl;
	switch (action->type_)
	{
	case LE_Type::MOVE:
		action->game_object_->scene_node_->setPosition(action->old_vec_);
		action_queue.pop_back();
		moveTools();
		break;
	case LE_Type::SCALE:
		action->game_object_->scene_node_->setScale(action->old_vec_);
		action_queue.pop_back();
		break;
	case LE_Type::ROTATE:
		action->game_object_->scene_node_->setOrientation(action->old_rot_);
		action_queue.pop_back();
		break;
	case LE_Type::DUPLICATE:
		GameObject* ptr;
		ptr = action->game_object_;
		std::cout << "Cringe" << std::endl;
		game_object_list_.remove(action->game_object_);
		delete action->game_object_;
		if (action->game_object_ == selected_object_) {
			selected_object_ = nullptr;
		}
		action_queue.pop_back();
		break;
	case LE_Type::DELETE:
		game_object_list_.push_back(new GameObject(scene_manager_, action->mesh_file_name_,
			action->old_vec_, action->new_vec_, true, action->is_visible_,
			action->old_rot_, action->axis_));
		action_queue.pop_back();
		break;
	default:
		break;
	}
	std::cout << action_queue.size() << std::endl;
}