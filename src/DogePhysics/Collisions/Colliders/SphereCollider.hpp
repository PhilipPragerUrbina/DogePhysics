//
// Created by Philip on 1/17/2023.
//

#pragma once

#include "Collider.hpp"

namespace Doge {

    /**
     * Collide spheres
     */
    class SphereCollider : public Collider{
    public:
        /**
         * Create a sphere collider
         * @param radius Radius of sphere
         * @param offset Object space offset from parent origin
         */
        SphereCollider(real radius, const Vector3& offset= {0}) : offset(offset), sphere(offset,radius){

        }

        void setParentTransform( Transformable *parent_transform) override {
            sphere.position = parent_transform->getPosition() + offset;
        }

        BoundingSphere getBounding() const override {
            return sphere;
        }

        Matrix3 createInertiaTensor(real mass) const override {
            Doge::Matrix3 mat{};
            mat.data[0][0]= (2.0/5.0) * mass * sphere.radius * sphere.radius; //Sphere
            mat.data[1][1]= mat.data[0][0]; //same
            mat.data[2][2]= mat.data[0][0]; //same
            return mat;
        }

        bool collide(const Collider *collider, CollisionData &data) const override {
            return collider->collide(*this,data);
        }

        bool collide(const SphereCollider &collider, CollisionData &data) const override {
            if(! sphere.checkOverlap(collider.sphere)){
                return false;
            }
            Vector3 direction = (sphere.position - collider.sphere.position).normalized(); //collider to this
            data.r2 = sphere.position + -direction * sphere.radius - sphere.position;
            data.r1 = collider.sphere.position + direction * (collider.sphere.radius)- collider.sphere.position;

            data.normal = direction;
            //positive
            data.depth = (sphere.radius + collider.sphere.radius) - collider.sphere.position.distance(sphere.position); //todo clean up and optimize

            return true;
        }
        bool collide(const CapsuleCollider &collider, CollisionData &data) const override {return false;}//todo default behavior of ret false so unimplented methods dont need to be specified


        bool collide(const BoxCollider &collider, CollisionData &data) const override {
            return false;
        }

    private:
        Vector3 offset;
        BoundingSphere sphere; //Already does job
        Transformable* transform;

    };

} // Doge
