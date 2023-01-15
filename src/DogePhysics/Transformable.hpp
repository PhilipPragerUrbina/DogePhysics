//
// Created by Philip on 1/9/2023.
//

#pragma once


#include "../Utils/Vector3.hpp"
#include "../Utils/Quaternion.hpp"

namespace Doge {

    //todo world vs object space
    /**
     * An object that exists in 3d space with position,rotation and scale
     */
    class Transformable{
    protected:
        //Transform
        Vector3 position = 0;
        Vector3 scale = 1;
        Quaternion rotation;
    public:

        /**
         * Get the scale in meters
         */
        Vector3 getScale() const {
            return scale;
        }

        /**
         * Set the scale in meters
         */
        void setScale(const Vector3& new_scale){
            scale = new_scale;
        }

        /**
         * Get rotation/orientation
         */
        Quaternion getRotation() const {
            return rotation;
        }

        /**
        * Set rotation/orientation
        */
        void setRotation(const Quaternion& new_rotation) {
            rotation = new_rotation;
        }

        /**
         * Get the position of this object in meters
         */
        Vector3 getPosition() const {
            return position;
        }

        /**
         * Set the position of the object in meters
         */
        void setPosition(const Vector3& new_position){
            position = new_position;
        }
    };

} // Doge
