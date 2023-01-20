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

    void setParentTransform(const Transformable *parent_transform) override {
        //todo next up. Make axis aligned box, and then rotating box!
    }

    BoundingSphere getBounding() const override {
        return BoundingSphere(Doge::Vector3(), 0);
    }

    Matrix3 createInertiaTensor(real mass) const override {
        return Matrix3();
    }

    bool collide(const SphereCollider &collider, CollisionData &data) const override {
        return false;
    }

    bool collide(const BoxCollider &collider, CollisionData &data) const override {
        return false;
    }


};

} // Doge
