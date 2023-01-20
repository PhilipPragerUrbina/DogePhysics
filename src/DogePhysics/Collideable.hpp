//
// Created by Philip on 1/9/2023.
//

#pragma once

#include "Transformable.hpp"
#include "Collisions/Colliders/Collider.hpp"

namespace Doge {

    /**
     * Has a collider
     */
    class Collideable : public virtual Transformable{
    private:
        std::unique_ptr<Collider> collider;
    public:
        Collideable(Collider* collider) : collider(collider){

        }

        //todo doc
        Collider* getCollider() const {
            collider->setParentTransform(this);
            return collider.get();
        }

    };

} // Doge
