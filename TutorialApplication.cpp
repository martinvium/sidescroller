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
}

//-------------------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void)
{
}

//-------------------------------------------------------------------------------------
void TutorialApplication::createScene(void)
{
    // Set the default lighting.
    mSceneMgr->setAmbientLight(Ogre::ColourValue(1.0f, 1.0f, 1.0f));
    
    createTerrain();
    createPlayer();
    
    // Create the walking list
    mWalkList.push_back(Ogre::Vector3(550.0f,  0.0f,  50.0f ));
    mWalkList.push_back(Ogre::Vector3(550.0f, 0.0f,  -200.0f ));
    mWalkList.push_back(Ogre::Vector3(-100.0f,  0.0f, -200.0f));
    
    // Create objects so we can see movement
    Ogre::Entity *ent;
    Ogre::SceneNode *node;

    ent = mSceneMgr->createEntity("Knot1", "knot.mesh");
    node = mSceneMgr->getRootSceneNode()->createChildSceneNode("Knot1Node",
        Ogre::Vector3(0.0f, -10.0f,  25.0f));
    node->attachObject(ent);
    node->setScale(0.1f, 0.1f, 0.1f);

    ent = mSceneMgr->createEntity("Knot2", "knot.mesh");
    node = mSceneMgr->getRootSceneNode()->createChildSceneNode("Knot2Node",
        Ogre::Vector3(550.0f, -10.0f,  50.0f));
    node->attachObject(ent);
    node->setScale(0.1f, 0.1f, 0.1f);
    
    ent = mSceneMgr->createEntity("Knot3", "knot.mesh");
    node = mSceneMgr->getRootSceneNode()->createChildSceneNode("Knot3Node",
        Ogre::Vector3(550.0f, -10.0f,  -200.0f));
    node->attachObject(ent);
    node->setScale(0.1f, 0.1f, 0.1f);

    ent = mSceneMgr->createEntity("Knot4", "knot.mesh");
    node = mSceneMgr->getRootSceneNode()->createChildSceneNode("Knot4Node",
        Ogre::Vector3(-100.0f, -10.0f,-200.0f));
    node->attachObject(ent);
    node->setScale(0.1f, 0.1f, 0.1f);
    
    // Set the camera to look at our handiwork
    mCamera->setPosition(90.0f, 280.0f, 535.0f);
    mCamera->pitch(Ogre::Degree(-30.0f));
    mCamera->yaw(Ogre::Degree(-15.0f));
    
    // Set idle animation
    mAnimationState = mEntity->getAnimationState("Idle");
    mAnimationState->setLoop(true);
    mAnimationState->setEnabled(true);
}

//-------------------------------------------------------------------------------------
void TutorialApplication::createTerrain(void)
{
    createBox("Cube1", Ogre::Vector3(100.0f, 0.0f, 25.0f));
    createBox("Cube2", Ogre::Vector3(300.0f, -100.0f, 25.0f));
    createBox("Cube3", Ogre::Vector3(500.0f, 50.0f, 25.0f));
}

//-------------------------------------------------------------------------------------
void TutorialApplication::createPlayer(void)
{
    // Create the entity
    mEntity = mSceneMgr->createEntity("Leroy", "robot.mesh");

    // Create the scene node
    mNode = mSceneMgr->getRootSceneNode()->
        createChildSceneNode("RobotNode", Ogre::Vector3(0.0f, 0.0f, 25.0f));
    mNode->attachObject(mEntity);
}

//-------------------------------------------------------------------------------------
void TutorialApplication::createBox(const Ogre::String &name, const Ogre::Vector3 &pos)
{
    // Create the entity
    Ogre::Entity *entityCube = mSceneMgr->createEntity("Entity" + name, "cube.mesh");
    entityCube->setMaterialName("Examples/Rockwall");
    entityCube->setCastShadows(false);
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
     mWalkSpeed = 35.0f;
     mDirection = Ogre::Vector3::ZERO;
}

//-------------------------------------------------------------------------------------
bool TutorialApplication::nextLocation(void)
{
    if (mWalkList.empty())
         return false;
    
    mDestination = mWalkList.front();  // this gets the front of the deque
    mWalkList.pop_front();             // this removes the front of the deque

    mDirection = mDestination - mNode->getPosition();
    mDistance = mDirection.normalise();
    
    return true;
}

//-------------------------------------------------------------------------------------
bool TutorialApplication::frameRenderingQueued(const Ogre::FrameEvent &evt)
{
    if (mDirection == Ogre::Vector3::ZERO) {
        if (nextLocation()) {
            // Set walking animation
            mAnimationState = mEntity->getAnimationState("Walk");
            mAnimationState->setLoop(true);
            mAnimationState->setEnabled(true);
        }
    } else {
        Ogre::Real move = mWalkSpeed * evt.timeSinceLastFrame;
        mDistance -= move;
    
        if (mDistance <= 0.0f) {
            mNode->setPosition(mDestination);
            mDirection = Ogre::Vector3::ZERO;

            // Set animation based on if the robot has another point to walk to. 
            if (! nextLocation()) {
                // Set Idle animation                     
                mAnimationState = mEntity->getAnimationState("Idle");
                mAnimationState->setLoop(true);
                mAnimationState->setEnabled(true);
            } else {
                Ogre::Vector3 src = mNode->getOrientation() * Ogre::Vector3::UNIT_X;
                if ((1.0f + src.dotProduct(mDirection)) < 0.0001f) {
                    mNode->yaw(Ogre::Degree(180));
                } else {
                    Ogre::Quaternion quat = src.getRotationTo(mDirection);
                    mNode->rotate(quat);
                }
            }
        } else {
            mNode->translate(mDirection * move);
        }
    }
    
    mAnimationState->addTime(evt.timeSinceLastFrame);
    
    return BaseApplication::frameRenderingQueued(evt);
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
