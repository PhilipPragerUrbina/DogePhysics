//
// Created by Philip on 1/9/2023.
//

#pragma once

#include "Collider.hpp"

namespace Doge {

    /**
     * Basic Bounding Box collision
     */
    class BoxCollider : public Collider{
    public:
        /**
         * Collide with any other object by passing self
         */
       bool collide(const Collider *collider, CollisionData &data) const override {
            return collider->collide(*this,data);
       }




    };

} // Doge
