# Awesome Sidescroller #1
A short description will come whenever

## GameStates
Application is very simple, and starts a gamestate, that contains all the 
initialization currently in application.

[Further reading](http://www.ogre3d.org/tikiwiki/Managing+Game+States+with+OGRE)

## Entity Components
[Further reading](http://www.ogre3d.org/forums/viewtopic.php?f=1&t=53302) and 
[even further](http://stackoverflow.com/questions/1901251/component-based-game-engine-design).

```cpp
EntityComponents/MoveComponent
EntityComponents/MoveComponentManager

for(it = mManager->iterator(); moveComp = it.next(); it.end()) {
    moveComp.update();
}

myEntity = ...
mManager.getComponent(myEntity).moveLeft();
mManager.getComponent(myEntity).moveRight();
```

alt

```cpp
myEntity->getComponent<MoveComponent>()->moveLeft()
myEntity->getComponent<MoveComponent>()->moveRight()
```
