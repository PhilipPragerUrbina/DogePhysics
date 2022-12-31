//
// Created by Philip on 12/27/2022.
//

#pragma once

#include "../Utils/Vector3.hpp"
#include "Renderer.hpp"

namespace Doge {

    /**
     * A renderer api agnostic basic camera
     * Is not able to change FOV or projection
     * Changes its position and rotation by pushing a transformation matrix to a renderer
     * Y is up
     */
    class Camera {
    private:
        Vector3 position;
        Vector3 direction;
    public:
        /**
         * Create a new camera
         * @param pos It's position in the world
         * @param dir The direction it's facing
         * @param up_direction Which direction is up
         */
        Camera(const Vector3& pos, const Vector3& dir): position(pos) , direction(dir){}

        /**
         * Push it's current transformation matrix to a renderer
         * Must be done every time camera is changed
         * Make sure to pop(Everything in between push and pop will use this camera)
         * @param renderer The renderer to apply to.
         */
        void push(Renderer& renderer) {
            renderer.pushMatrix();
            renderer.lookAt(position,position+direction,{0,1,0});
        }


        /**
         * Pops the camera's transformation matrix
         * Assumes all other matrices pushed in between the camera's push have been properly popped as well
         * @param renderer
         */
        void pop(Renderer& renderer) {
            renderer.popMatrix();
        }

        /**
         * Get the position of the camera
         */
        Vector3 getPosition() const {
            return position;
        }
        /**
         * Set the position of the camera
         */
        void setPosition(const Vector3 &new_position) {
            position = new_position;
        }
        /**
         * Get the direction the camera is facing in
         */
        Vector3 getDirection() const {
            return direction;
        }
        /**
          * Set the direction the camera is facing in
          * Does not need to be normalized(Will normalize)
          */
        void setDirection(const Vector3 &new_direction) {
            direction = new_direction.normalized(); //make sure its normalized
        }

    };

} // Doge
