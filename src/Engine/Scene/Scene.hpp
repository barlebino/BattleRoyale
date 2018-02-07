/* Scene 
 * Contains data structures for systems, game objects, and components */
#pragma once
#ifndef _SCENE_HPP_
#define _SCENE_HPP_

#include "System/Systems.hpp"

#include "GameObject/GameObject.hpp"
#include "Component/Components.hpp"

#include <map>
#include <vector>

class Scene {
    public:
        enum SystemType{
            GAMELOGIC,
            RENDERABLE
        };
        Scene();
 
        /* Systems */
        GameLogicSystem *gameLogic;
        RenderSystem *renderer;

        /* Game Objects */
        GameObject* createGameObject();
        void addGameObject(GameObject *);
    
        /* Components */
        template<SystemType V, class T, class... Args>
        T* createComponent(Args&&... args) {
            T* ptr = new T(args...);
            addComponent(V, ptr);
            return ptr;
        }
        void addComponent(SystemType, Component *);

        /* Main udate function */
        void update(float);

        /* Destroy everything */
        void shutDown();
    private:
        /* Lists of all game objects */
        std::vector<GameObject *> allGameObjects;

        /* List of all systems and their component lists */
        std::map<SystemType, std::vector<Component *>> allComponents;

        /* Instantiate/Kill queues */
        void addNewObjects();
        void terminateObjects();
        std::vector<GameObject *> newGameObjectQueue;
        std::map<SystemType, std::vector<Component *>> newComponentQueue;
};

#endif