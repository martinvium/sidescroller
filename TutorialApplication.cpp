/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.cpp
-----------------------------------------------------------------------------

This source file is part of the
   ___                 __    __ _ _    _ 
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
      |___/                              
      Tutorial Framework
      http://www.ogre3d.org/tikiwiki/
-----------------------------------------------------------------------------
*/
#include "TutorialApplication.h"
#include <OgreManualObject.h>
#include <OgreRenderOperation.h>
#include <OgreResourceGroupManager.h>
#include <OgreString.h>

//-------------------------------------------------------------------------------------
TutorialApplication::TutorialApplication(void)
{
    mCameraLocked = true;
}

//-------------------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void)
{
}

//-------------------------------------------------------------------------------------
void TutorialApplication::createScene(void)
{
    // Set the default lighting.
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));
    mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
    
    createTerrain();
    createPlayer();
    
    // Create the walking list
    mWalkList.push_back(Ogre::Vector3(200.0f,  10.0f,  35.0f ));
    mWalkList.push_back(Ogre::Vector3(0.0f, 10.0f,  35.0f ));
    mWalkList.push_back(Ogre::Vector3(200.0f,  10.0f, 35.0f));
    
    // Set the camera to look at our handiwork
    mCamera->setPosition(90.0f, CAMERA_Y, CAMERA_Z);
    mCamera->pitch(Ogre::Degree(-30.0f));
    mCamera->yaw(Ogre::Degree(-15.0f));
    
    // Set idle animation
    mAnimationState = mPlayerEntity->getAnimationState("Idle");
    mAnimationState->setLoop(true);
    mAnimationState->setEnabled(true);
}

//-------------------------------------------------------------------------------------
void TutorialApplication::createTerrain(void)
{
    createBackground();
    createLava();
    createBox("Cube1", Ogre::Vector3(100.0f, 0.0f, 25.0f));
    createBox("Cube2", Ogre::Vector3(300.0f, -100.0f, 25.0f));
    createBox("Cube3", Ogre::Vector3(500.0f, 50.0f, 25.0f));
}

//-------------------------------------------------------------------------------------
void TutorialApplication::createBackground(void)
{
    // wall
    Ogre::Plane wallPlane(Ogre::Vector3::UNIT_Z, 0);
    Ogre::MeshManager::getSingleton().createPlane("wall", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        wallPlane, 1500, 1500, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Y);
    
    Ogre::Entity* entWall = mSceneMgr->createEntity("WallEntity", "wall");
    Ogre::SceneNode *nodeWall = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    nodeWall->attachObject(entWall);
    nodeWall->setPosition(Ogre::Vector3(0.0f, 0.0f, -25.0f));
    
    entWall->setMaterialName("Examples/Rockwall");
    entWall->setCastShadows(false);
}

//-------------------------------------------------------------------------------------
void TutorialApplication::createLava(void)
{
    Ogre::Plane lavaPlane(Ogre::Vector3::UNIT_Y, 0);
    Ogre::MeshManager::getSingleton().createPlane("lava", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        lavaPlane, 1500, 1500, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
    
    Ogre::Entity* entLava = mSceneMgr->createEntity("LavaEntity", "lava");
    Ogre::SceneNode *nodeLava = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    nodeLava->attachObject(entLava);
    nodeLava->setPosition(Ogre::Vector3(0.0f, -150.0f, 0.0f));
    
    entLava->setMaterialName("Environment/Lava");
    entLava->setCastShadows(false);
    
    createLavaLight();
}

//-------------------------------------------------------------------------------------
void TutorialApplication::createLavaLight(void)
{
    Ogre::Light* pointLight = mSceneMgr->createLight("pointLight1");
    pointLight->setType(Ogre::Light::LT_POINT);
    pointLight->setPosition(Ogre::Vector3(-50, -100, 50));
    pointLight->setDiffuseColour(Ogre::ColourValue(1, 0, 0));
    pointLight->setSpecularColour(Ogre::ColourValue(.25, 0, 0));
    
    Ogre::Light* pointLight2 = mSceneMgr->createLight("pointLight2");
    pointLight2->setType(Ogre::Light::LT_POINT);
    pointLight2->setPosition(Ogre::Vector3(200, -100, 50));
    pointLight2->setDiffuseColour(Ogre::ColourValue(1, 0, 0));
    pointLight2->setSpecularColour(Ogre::ColourValue(.25, 0, 0));
    
    Ogre::Light* pointLight3 = mSceneMgr->createLight("pointLight3");
    pointLight3->setType(Ogre::Light::LT_POINT);
    pointLight3->setPosition(Ogre::Vector3(400, -100, 50));
    pointLight3->setDiffuseColour(Ogre::ColourValue(1, 0, 0));
    pointLight3->setSpecularColour(Ogre::ColourValue(.25, 0, 0));
}

//-------------------------------------------------------------------------------------
void TutorialApplication::createPlayer(void)
{
    // Create the entity
    mPlayerEntity = mSceneMgr->createEntity("Leroy", "robot.mesh");
    mPlayerEntity->setCastShadows(false);

    // Create the scene node
    mPlayerNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("RobotNode", Ogre::Vector3(0.0f, 10.0f, 35.0f));
    mPlayerNode->attachObject(mPlayerEntity);
    
    mCameraMan->setTarget(mPlayerNode);
}

//-------------------------------------------------------------------------------------
void TutorialApplication::createBox(const Ogre::String &name, const Ogre::Vector3 &pos)
{
    // Create the entity
    Ogre::Entity *entityCube = mSceneMgr->createEntity("Entity" + name, "cube.mesh");
    entityCube->setMaterialName("Examples/Rockwall");
    entityCube->setCastShadows(true);
    //mBoxEntities->push_back(*entityCube);

    // Create the scene node
    Ogre::SceneNode *nodeCube = mSceneMgr->getRootSceneNode()->createChildSceneNode("Node" + name, pos);
    nodeCube->attachObject(entityCube);
    nodeCube->setScale(2.0f, 0.2f, 1.0f);
    //mBoxNodes->push_back(*nodeCube);
}

//-------------------------------------------------------------------------------------
void TutorialApplication::createFrameListener(void)
{
    BaseApplication::createFrameListener();
    
    // Set default values for variables
     mWalkSpeed = 25.0f;
     mDirection = Ogre::Vector3::ZERO;
}

//-------------------------------------------------------------------------------------
bool TutorialApplication::nextLocation(void)
{
    if (mWalkList.empty())
         return false;
    
    mDestination = mWalkList.front();  // this gets the front of the deque
    mWalkList.pop_front();             // this removes the front of the deque

    mDirection = mDestination - mPlayerNode->getPosition();
    mDistance = mDirection.normalise();
    
    return true;
}

//-------------------------------------------------------------------------------------
bool TutorialApplication::frameRenderingQueued(const Ogre::FrameEvent &evt)
{
    movePlayer(evt);
    
    return BaseApplication::frameRenderingQueued(evt);
}

//-------------------------------------------------------------------------------------
void TutorialApplication::movePlayer(const Ogre::FrameEvent &evt)
{
    if (mDirection == Ogre::Vector3::ZERO) {
        if (nextLocation()) {
            // Set walking animation
            mAnimationState = mPlayerEntity->getAnimationState("Walk");
            mAnimationState->setLoop(true);
            mAnimationState->setEnabled(true);
        }
    } else {
        Ogre::Real move = mWalkSpeed * evt.timeSinceLastFrame;
        mDistance -= move;
    
        if (mDistance <= 0.0f) {
            mPlayerNode->setPosition(mDestination);
            mDirection = Ogre::Vector3::ZERO;

            // Set animation based on if the robot has another point to walk to. 
            if (! nextLocation()) {
                // Set Idle animation                     
                mAnimationState = mPlayerEntity->getAnimationState("Idle");
                mAnimationState->setLoop(true);
                mAnimationState->setEnabled(true);
            } else {
                Ogre::Vector3 src = mPlayerNode->getOrientation() * Ogre::Vector3::UNIT_X;
                if ((1.0f + src.dotProduct(mDirection)) < 0.0001f) {
                    mPlayerNode->yaw(Ogre::Degree(180));
                } else {
                    Ogre::Quaternion quat = src.getRotationTo(mDirection);
                    mPlayerNode->rotate(quat);
                }
            }
        } else {
            mPlayerNode->translate(mDirection * move);
            //Ogre::Vector3 pos = mNode->getPosition();
            //mCamera->setPosition(pos.x, CAMERA_Y, CAMERA_Z);
        }
    }
    
    mAnimationState->addTime(evt.timeSinceLastFrame);
}

bool TutorialApplication::keyPressed( const OIS::KeyEvent &arg )
{
    bool ret = BaseApplication::keyPressed(arg);
    return ret;
}


#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        TutorialApplication app;

        try {
            app.go();
        } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occured: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif
