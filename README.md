# Awesome Sidescroller #1
A short description will come whenever

# TODO
## GameStates
Application is very simple, and starts a gamestate, that contains all the 
initialization currently in application.

## Entity Components ?
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
