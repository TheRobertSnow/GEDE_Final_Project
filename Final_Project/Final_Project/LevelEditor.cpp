#include "pch.h"
#include "LevelEditor.h"
#include "ObjectController.h"

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
	setupObjectController();
	populateScene();
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

void LevelEditor::setupObjectController()
{
	object_controller_ = new ObjectController();
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
	GameObject* newObj = new GameObject(scene_manager_, "cube.mesh", Vector3(0, 3, 0), Vector3(0.01, 0.01, 0.01));
	game_object_list_.push_back(newObj);

	// move arrows
	move_x_arrow_entity_ = scene_manager_->createEntity("X_arrow.mesh");
	move_x_arrow_entity_node_ = scene_manager_->getRootSceneNode()->createChildSceneNode();
	move_x_arrow_entity_node_->attachObject(move_x_arrow_entity_);
	move_x_arrow_entity_node_->setPosition(Vector3(2, 0, 0));
	move_x_arrow_entity_node_->setScale(Vector3(1, 1, 1));
	move_x_arrow_entity_node_->yaw(Ogre::Degree(270));
	move_x_arrow_entity_->setCastShadows(false);
	move_x_arrow_entity_node_->setVisible(false);

	move_y_arrow_entity_ = scene_manager_->createEntity("Y_arrow.mesh");
	move_y_arrow_entity_node_ = scene_manager_->getRootSceneNode()->createChildSceneNode();
	move_y_arrow_entity_node_->attachObject(move_y_arrow_entity_);
	move_y_arrow_entity_node_->setPosition(Vector3(0, 2, 0));
	move_y_arrow_entity_node_->setScale(Vector3(1, 1, 1));
	move_y_arrow_entity_node_->pitch(Ogre::Degree(90));
	move_y_arrow_entity_->setCastShadows(false);
	move_y_arrow_entity_node_->setVisible(false);

	move_z_arrow_entity_ = scene_manager_->createEntity("Z_arrow.mesh");
	move_z_arrow_entity_node_ = scene_manager_->getRootSceneNode()->createChildSceneNode();
	move_z_arrow_entity_node_->attachObject(move_z_arrow_entity_);
	move_z_arrow_entity_node_->setPosition(Vector3(0, 0, 2));
	move_z_arrow_entity_node_->setScale(Vector3(1, 1, 1));
	move_z_arrow_entity_node_->yaw(Ogre::Degree(180));
	move_z_arrow_entity_->setCastShadows(false);
	move_z_arrow_entity_node_->setVisible(false);

	// scale arrows
	scale_x_arrow_entity_ = scene_manager_->createEntity("X_arrow.mesh");
	scale_x_arrow_entity_node_ = scene_manager_->getRootSceneNode()->createChildSceneNode();
	scale_x_arrow_entity_node_->attachObject(scale_x_arrow_entity_);
	scale_x_arrow_entity_node_->setPosition(Vector3(2, 0, 0));
	scale_x_arrow_entity_node_->setScale(Vector3(1, 1, 1));
	scale_x_arrow_entity_node_->yaw(Ogre::Degree(270));
	scale_x_arrow_entity_->setCastShadows(false);
	scale_x_arrow_entity_node_->setVisible(false);

	scale_y_arrow_entity_ = scene_manager_->createEntity("Y_arrow.mesh");
	scale_y_arrow_entity_node_ = scene_manager_->getRootSceneNode()->createChildSceneNode();
	scale_y_arrow_entity_node_->attachObject(scale_y_arrow_entity_);
	scale_y_arrow_entity_node_->setPosition(Vector3(0, 2, 0));
	scale_y_arrow_entity_node_->setScale(Vector3(1, 1, 1));
	scale_y_arrow_entity_node_->pitch(Ogre::Degree(90));
	scale_y_arrow_entity_->setCastShadows(false);
	scale_y_arrow_entity_node_->setVisible(false);

	scale_z_arrow_entity_ = scene_manager_->createEntity("Z_arrow.mesh");
	scale_z_arrow_entity_node_ = scene_manager_->getRootSceneNode()->createChildSceneNode();
	scale_z_arrow_entity_node_->attachObject(scale_z_arrow_entity_);
	scale_z_arrow_entity_node_->setPosition(Vector3(0, 0, 2));
	scale_z_arrow_entity_node_->setScale(Vector3(1, 1, 1));
	scale_z_arrow_entity_node_->yaw(Ogre::Degree(180));
	scale_z_arrow_entity_->setCastShadows(false);
	scale_z_arrow_entity_node_->setVisible(false);
}

bool LevelEditor::frameStarted(const Ogre::FrameEvent& evt)
{
	ApplicationContext::frameStarted(evt);
	// Store the time that has passed since last time we got the callback
	const Ogre::Real delta_time = evt.timeSinceLastFrame;
	// Check what keys of the keyboard are being pressed
	const Uint8* state = SDL_GetKeyboardState(nullptr);
	SDL_Point p;
	const Uint32 mouse_state = SDL_GetMouseState(&p.x, &p.y);

	// Manage new input in input manager
	input_manager_->update(state, &mouse_state);

	if (state[SDL_SCANCODE_LCTRL])
	{
		if (state[SDL_SCANCODE_D])
		{
			if (!d_pressed_)
			{
				d_pressed_ = true;
				if (selected_object_ != nullptr) duplicateSelectedGameObject();
			}
		}
		else
		{
			d_pressed_ = false;
		}
	}
	// update the roaming camera
	if (roaming_camera_ != nullptr) roaming_camera_->update(delta_time, state);

	// Move Button
	if (xPressed) {
		move_x_arrow_entity_node_->setVisible(true);
		move_y_arrow_entity_node_->setVisible(true);
		move_z_arrow_entity_node_->setVisible(true);
	}
	else {
		move_x_arrow_entity_node_->setVisible(false);
		move_y_arrow_entity_node_->setVisible(false);
		move_z_arrow_entity_node_->setVisible(false);
	}
	// Scale Button
	if (yPressed) {
		scale_x_arrow_entity_node_->setVisible(true);
		scale_y_arrow_entity_node_->setVisible(true);
		scale_z_arrow_entity_node_->setVisible(true);
	}
	else {
		scale_x_arrow_entity_node_->setVisible(false);
		scale_y_arrow_entity_node_->setVisible(false);
		scale_z_arrow_entity_node_->setVisible(false);
	}
	if (leftClickPressed)
	{
		if (selected_object_ != nullptr)
		{
			// Move Entities
			if (move_x_arrow_entity_node_->getShowBoundingBox())
			{
				object_controller_->MoveEntity(selected_object_->scene_node_, p, mousePos, delta_time, "x");
			}
			if (move_y_arrow_entity_node_->getShowBoundingBox())
			{
				object_controller_->MoveEntity(selected_object_->scene_node_, p, mousePos, delta_time, "y");
			}
			if (move_z_arrow_entity_node_->getShowBoundingBox())
			{
				object_controller_->MoveEntity(selected_object_->scene_node_, p, mousePos, delta_time, "z");
			}
			// Scale Entities
			if (scale_x_arrow_entity_node_->getShowBoundingBox())
			{
				object_controller_->ScaleEntity(selected_object_->scene_node_, p, mousePos, delta_time, "x");
			}
			if (scale_y_arrow_entity_node_->getShowBoundingBox())
			{
				object_controller_->ScaleEntity(selected_object_->scene_node_, p, mousePos, delta_time, "y");
			}
			if (scale_z_arrow_entity_node_->getShowBoundingBox())
			{
				object_controller_->ScaleEntity(selected_object_->scene_node_, p, mousePos, delta_time, "z");
			}
			leftClickPressed = false;
			//xPressed = false;
		}
	}
	mousePos = p;
	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(1)) {
		leftClickPressed = true;
	}
	if (selected_object_ != nullptr)
	{
		// Make Arrows Follow Selected Entity
		Vector3 selectedEntityPos = selected_object_->scene_node_->getPosition();
		Vector3 selectedEntityScale = selected_object_->scene_node_->getScale() * 50;
		move_x_arrow_entity_node_->setPosition(selectedEntityPos.x + 2 + selectedEntityScale.x, selectedEntityPos.y, selectedEntityPos.z);
		move_y_arrow_entity_node_->setPosition(selectedEntityPos.x, selectedEntityPos.y + 2 + selectedEntityScale.y, selectedEntityPos.z);
		move_z_arrow_entity_node_->setPosition(selectedEntityPos.x, selectedEntityPos.y, selectedEntityPos.z + 2 + selectedEntityScale.z);
		scale_x_arrow_entity_node_->setPosition(selectedEntityPos.x + 2 + selectedEntityScale.x, selectedEntityPos.y, selectedEntityPos.z);
		scale_y_arrow_entity_node_->setPosition(selectedEntityPos.x, selectedEntityPos.y + 2 + selectedEntityScale.y, selectedEntityPos.z);
		scale_z_arrow_entity_node_->setPosition(selectedEntityPos.x, selectedEntityPos.y, selectedEntityPos.z + 2 + selectedEntityScale.z);
	}
	return true;
}

bool LevelEditor::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == OgreBites::SDLK_ESCAPE)
	{
		getRoot()->queueEndRendering();
	}
	// x = 120
	else if (evt.keysym.sym == 120)
	{
		if (xPressed) {
			xPressed = false;
			move_x_arrow_entity_node_->showBoundingBox(false);
			move_y_arrow_entity_node_->showBoundingBox(false);
			move_z_arrow_entity_node_->showBoundingBox(false);
		}
		else {
			xPressed = true;
			yPressed = false;
		}
	}
	// y = 121
	else if (evt.keysym.sym == 121)
	{
		if (yPressed) {
			yPressed = false;
			scale_x_arrow_entity_node_->showBoundingBox(false);
			scale_y_arrow_entity_node_->showBoundingBox(false);
			scale_z_arrow_entity_node_->showBoundingBox(false);
		}
		else {
			yPressed = true;
			xPressed = false;
		}
	}
	else if (evt.keysym.sym == OgreBites::SDLK_DELETE)
	{
		removeSelectedGameObject();
	}
	/*else if (evt.keysym.sym == SDLK_LCTRL)
	{
		std::cout << "L_CTRL" << std::endl;
		if (d_pressed_)
		{
			duplicateSelectedGameObject();
		}
	}
	else if (evt.keysym.sym == SDLK_d)
	{
		std::cout << "Cum" << std::endl;
		d_pressed_ = true;
	}*/
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
					obj_was_selected = true;
					cout << "selected_object_: " << selected_object_ << endl << "list item: " << i << endl;
				}
			}
			if (!obj_was_selected)
			{
				if (selected_object_ != nullptr)
				{
					selected_object_->setSelected(false);
					selected_object_ = nullptr;
				}
			}

			leftClickPressed = true;
			// Check if ray intersects with box
			std::pair<bool, Ogre::Real> result_move_x = mouseRay.intersects(move_x_arrow_entity_node_->_getWorldAABB());
			std::pair<bool, Ogre::Real> result_move_y = mouseRay.intersects(move_y_arrow_entity_node_->_getWorldAABB());
			std::pair<bool, Ogre::Real> result_move_z = mouseRay.intersects(move_z_arrow_entity_node_->_getWorldAABB());
			std::pair<bool, Ogre::Real> result_scale_x = mouseRay.intersects(scale_x_arrow_entity_node_->_getWorldAABB());
			std::pair<bool, Ogre::Real> result_scale_y = mouseRay.intersects(scale_y_arrow_entity_node_->_getWorldAABB());
			std::pair<bool, Ogre::Real> result_scale_z = mouseRay.intersects(scale_z_arrow_entity_node_->_getWorldAABB());


			// Move Arrows
			if (result_move_x.first && xPressed)
			{
				move_x_arrow_entity_node_->showBoundingBox(true);
			}
			else
			{
				move_x_arrow_entity_node_->showBoundingBox(false);
			}
			if (result_move_y.first && xPressed)
			{
				move_y_arrow_entity_node_->showBoundingBox(true);
			}
			else
			{
				move_y_arrow_entity_node_->showBoundingBox(false);
			}
			if (result_move_z.first && xPressed)
			{
				move_z_arrow_entity_node_->showBoundingBox(true);
			}
			else
			{
				move_z_arrow_entity_node_->showBoundingBox(false);
			}
			// Scale Arrows
			if (result_scale_x.first && yPressed)
			{
				scale_x_arrow_entity_node_->showBoundingBox(true);
			}
			else
			{
				scale_x_arrow_entity_node_->showBoundingBox(false);
			}
			if (result_scale_y.first && yPressed)
			{
				scale_y_arrow_entity_node_->showBoundingBox(true);
			}
			else
			{
				scale_y_arrow_entity_node_->showBoundingBox(false);
			}
			if (result_scale_z.first && yPressed)
			{
				scale_z_arrow_entity_node_->showBoundingBox(true);
			}
			else
			{
				scale_z_arrow_entity_node_->showBoundingBox(false);
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
		std::cout << "Size of list: " << game_object_list_.size() << std::endl;
		// Destroy the GameObject and remove it from game_object_list_
		delete selected_object_;
		game_object_list_.remove(selected_object_);
		selected_object_ = nullptr;
		std::cout << "Size of list: " << game_object_list_.size() << std::endl;
	}
}

void LevelEditor::duplicateSelectedGameObject()
{
	game_object_list_.push_back(new GameObject(selected_object_));
}