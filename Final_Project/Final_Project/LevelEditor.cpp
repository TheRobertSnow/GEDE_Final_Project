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
	Ogre::Vector3 newSpawnPosition = Ogre::Vector3(0, 0, 0);
	object_entity_ = scene_manager_->createEntity("cube.mesh");
	object_entity_node_ = scene_manager_->getRootSceneNode()->createChildSceneNode();
	object_entity_node_->attachObject(object_entity_);
	object_entity_node_->setPosition(newSpawnPosition);
	object_entity_node_->setScale(Vector3(0.01, 0.01, 0.01));
	object_entity_->setCastShadows(true);
}

bool LevelEditor::frameStarted(const Ogre::FrameEvent& evt)
{
	ApplicationContext::frameStarted(evt);
	// Store the time that has passed since last time we got the callback
	const Ogre::Real delta_time = evt.timeSinceLastFrame;
	// Check what keys of the keyboard are being pressed
	const Uint8* state = SDL_GetKeyboardState(nullptr);
	if (roaming_camera_ != nullptr) roaming_camera_->update(delta_time, state);
	SDL_Point p;
	SDL_GetMouseState(&p.x, &p.y);
	if (xPressed)
	{
		object_controller_->MoveEntity(object_entity_node_, p, mousePos, delta_time, "x");
		xPressed = false;
	}
	else if (yPressed)
	{
		object_controller_->MoveEntity(object_entity_node_, p, mousePos, delta_time, "y");
		yPressed = false;
	}
	else if (zPressed)
	{
		object_controller_->MoveEntity(object_entity_node_, p, mousePos, delta_time, "z");
		zPressed = false;
	}
	else if (gPressed)
	{
		object_controller_->ScaleEntity(object_entity_node_, p, mousePos, delta_time, "x");
		gPressed = false;
	}
	else if (hPressed)
	{
		object_controller_->ScaleEntity(object_entity_node_, p, mousePos, delta_time, "y");
		hPressed = false;
	}
	else if (jPressed)
	{
		object_controller_->ScaleEntity(object_entity_node_, p, mousePos, delta_time, "z");
		jPressed = false;
	}
	else {
		mousePos = p;
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
		if (object_entity_node_->getShowBoundingBox())
		{
			xPressed = true;
		}
	}
	// y = 121
	else if (evt.keysym.sym == 121)
	{
		if (object_entity_node_->getShowBoundingBox())
		{
			yPressed = true;
		}
	}
	// z = 122
	else if (evt.keysym.sym == 122)
	{
		if (object_entity_node_->getShowBoundingBox())
		{
			zPressed = true;
		}
	}
	// g = 103
	else if (evt.keysym.sym == 103)
	{
		if (object_entity_node_->getShowBoundingBox())
		{
			gPressed = true;
		}
	}
	// h = 104
	else if (evt.keysym.sym == 104)
	{
		if (object_entity_node_->getShowBoundingBox())
		{
			hPressed = true;
		}
	}
	// j = 106
	else if (evt.keysym.sym == 106)
	{
		if (object_entity_node_->getShowBoundingBox())
		{
			jPressed = true;
		}
	}
	else {
		cout << evt.keysym.sym;
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
			leftClickPressed = true;
			// Check if ray intersects with box
			std::pair<bool, Ogre::Real> result = mouseRay.intersects(object_entity_node_->_getWorldAABB());

			// If box not selected
			if (result.first && !object_selected_)
			{
				object_entity_node_->showBoundingBox(true);
			}
			// If box is selected
			else 
			{
				object_entity_node_->showBoundingBox(false);
			}
		}
	}
	else if (evt.type == OgreBites::MOUSEBUTTONUP)
	{
		if (evt.button == OgreBites::BUTTON_LEFT)
		{
			leftClickPressed = false;
		}
	}
	return true;
}