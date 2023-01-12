//
// Created by Philip on 1/9/2023.
//

#pragma once


#include "../Utils/Vector3.hpp"

namespace Doge {

    /**
     * An object that exists in 3d space with position,rotation and scale
     */
    class Transformable{
    protected:
        //Transform
        Vector3 position = 0;
    public:

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
