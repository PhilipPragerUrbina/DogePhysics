//
// Created by Philip on 12/28/2022.
//

#pragma once

#include "GameObject.hpp"

namespace Doge {

    /**
     * Contains within it the scene. Thin wrapper.
     */
    class SceneGraph {
        //todo Serialization
        //todo Querying
    public:
        /**
         * Create a scene with a root node
         * @param root_node Node at top of hierarchy. Lifetime is now part of Scene graph.
         */
        SceneGraph(GameObject* root_node){
            root = root_node;
        }

        /**
          * Add a game-object as a child of the root node
          * It's lifetime will now be tied to this scene
          * @param game_object The new child to add
          */
        void addObject(GameObject* object){
            root->addChild(object);
        }


        /**
         * Update the scene. Run game and simulation logic.
         * @param delta_time Delta time for simulation. Time since last frame.
         */
        void update(real delta_time){
            root->GraphUpdate(delta_time);
        }

        /**
         * Render the scene to a renderer
         * @param renderer The renderer interface
         */
        void render(Renderer* renderer){
            root->GraphRender(renderer);
        }


        /**
         * Destroy the root node
         */
        ~SceneGraph(){
            delete root;
        }

    private:
        GameObject* root; //The topmost node
    };

} // Doge
