#include "pch.h"
#include "MainCamera.h"

MainCamera::MainCamera(SceneManager* scene_manager, RenderWindow*
	render_window, Vector3 position, Vector3 lookat_position)
{
	// Add camera
	camera_node_ = scene_manager_->getRootSceneNode()->createChildSceneNode();
	camera_ = scene_manager_->createCamera("MainCamera");

	camera_->setNearClipDistance(5);
	camera_->setAutoAspectRatio(true);

	camera_node_->setPosition(0, 10, 50);
	camera_node_->lookAt(Ogre::Vector3(0, 0, 0), Node::TransformSpace::TS_WORLD);
	camera_node_->attachObject(camera_);

	Viewport* vp = getRenderWindow()->addViewport(camera_);
	camera_->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

	// To match the BG color with the fog
	Ogre::ColourValue fadeColour(0.9, 0.9, 0.9);
	vp->setBackgroundColour(fadeColour);

	// Add fog that starts 50 units away from the camera, ends at 300 units, and increases in a linear fashion
	scene_manager_->setFog(Ogre::FOG_LINEAR, fadeColour, 0, 50, 300);
}

MainCamera::~MainCamera()
{

}