//
// Created by Philip on 12/28/2022.
//

#pragma once

#include <vector>
#include "../../Utils/Vector3.hpp"
#include "../../Renderer/Renderer.hpp"
#include "../../Utils/Quaternion.hpp"

namespace Doge {

    /**
     * A component of our scene graph
     * Should be extended to create the objects within your game
     */
    class GameObject {
    private:

        unsigned int child_id; // The identifier that is unique to each child of a parent

        GameObject* parent = nullptr; //The parent of this game object
        std::vector<GameObject*> children; //The children of this node

    protected:

        /**
         * Specify what should happen every frame
         * Use the renderer to render your object. Draw shapes or meshes.
         * The transforms of this object have already been applied, but you can add additional ones as well.
         * @warning Make sure to match all pushMatrix, with a popMatrix.
         * Children of this object will be automatically rendered, you do not need to call render on them here.
         * @param renderer The rendering interface
         */
        virtual void render(Renderer* renderer) = 0;

        /**
         * This is your "script"
         * Create game logic here.
         * Also make sure to simulate your physics here as well.
         * Children of this object will be automatically updated, so you do not need to update them here
         * @param delta_time Delta time for simulation
         */
        virtual void update(real delta_time) =0 ;

        /**
           * Set a child node's parent
           * @param new_parent Pointer to parent node
           * @param new_child_id Index of the child in the parent's array. Unique for the parents children.
           */
        void setParent(GameObject* new_parent, unsigned int new_child_id){
            parent = new_parent;
            child_id = new_child_id;
        }

    public:

        //Fundamental attributes
        Vector3 position;
        Doge::Quaternion rotation;
        Vector3 scale = 1;

        //Material
        Vector3 color = {255,255,255};

        /**
         * Update this node and it's children
         * @param delta_time Delta time for simulation
         */
        void GraphUpdate(const real delta_time){

            update(delta_time); //update self

            for (GameObject* game_object : children) {
                game_object->GraphUpdate(delta_time); //update children
            }
        }

        /**
         * Render this node and it's children
         * @param renderer Render interface to use
         */
        void GraphRender(Renderer* renderer){
            //Apply transforms
            renderer->pushMatrix();
            renderer->translate(position);
            renderer->rotate(rotation);
          //todo figure out how rotation works
          //todo add pre made transformation matrix to push, rather than recalculating every frame. Can be directly gotten from the physics engine
            renderer->scale(scale);

            renderer->setColor(color.x,color.y,color.z);
            render(renderer); //render self

            for (GameObject* game_object : children) {
                game_object->GraphRender(renderer); //render children
            }

            renderer->popMatrix();
        }

        /**
         * The children are destroyed when the parent is destroyed
         */
        virtual ~GameObject(){
            for (GameObject* game_object : children) {
                delete game_object;
            }
        }

        /**
         * Add a game-object as a child
         * It's lifetime will now be tied to this node
         * @param game_object The new child to add
         * @return The child_id of the object, to be able to access it with getChild()
         */
        unsigned int addChild(GameObject* game_object){
            game_object->setParent(this,children.size());
            children.push_back(game_object);
            return children.size()-1;
        }

        /**
         * Get a child GameObject
         * @param id Child id or index
         * @return Pointer to child node. Nullptr if not found.
         */
        GameObject* getChild(unsigned int id){
            if(id < children.size()){
                return children[id];
            }
            return nullptr; //not found
        }

        /**
         * Get Pointer to parent node
         */
        GameObject* getParent(){
            return parent;
        }

        //todo key input events. if(getKeyPressed()) would be preferable to keyPressCallback()

        //Todo destroyChild() and destroy(): parent.destroyChild(child_id)

    };

} // Doge
