//
// Created by Philip on 1/9/2023.
//

#pragma once

#include "../../../Utils/BoundingSphere.hpp"
#include "../../Transformable.hpp"





namespace Doge {
    //predeclare
    class Collideable;
    class BoxCollider;
    class SphereCollider;
    class CapsuleCollider;

    /**
     * Data from collision
     */
    struct CollisionData{
        Vector3 r1,r2; //Position of hit
        Vector3 normal; //Normal of hit
        real depth; //Penetration depth
        Collideable* a;
        Collideable* b; //Bodies that collided 1 and 2 respectively. To be assigned by collision layer, not the collision check.
        //todo calculate r1 and r2 here
        //todo normal is in what direction
        Vector3 lambda;
    };

    /**
     * Detects collisions
     */
    class Collider {
    public:
        Vector3 velocity;

        /**
         * Update world space transform of collider to reflect object transform.
         * Separate from any relative transform of collider(such as offsetting a box)
         * This should be called by collidable before collision detection
         * @param transformable Transform of object this collider is attached to
         */
        virtual void setParentTransform( Transformable* parent_transform) = 0; //todo is pointer or value

        /**
         * Get the bounding sphere of the collider in world space
         */
        virtual BoundingSphere getBounding() const = 0;

        /**
         * Generate and get the inertia tensor of the collider in object space based on a mass
         * Usually only called once by collidable
         * @return Inertia tensor
         */
        virtual Matrix3 createInertiaTensor(real mass) const = 0;

        /**
         * Perform a coarse bounding collision check
         * @param other Other to collide to
         * @return True if detected.
         * todo doc
         */
        bool coarseCollision(const Collider* other, real delta_time, real k =1) const{
            BoundingSphere a = other->getBounding(); //todo doc accounting for movement
            a.radius += other->velocity.length() * k * delta_time;
            BoundingSphere b = getBounding();
            b.radius += velocity.length() * k * delta_time;
            return a.checkOverlap(b);
        }



        /**
         * Main Collision detection method, uses polymorphism trick to call the specific overloaded collision detection methods.
        * Check collision with any supported collider
        * @param collider Collider to check collision with
        * @param data Put collision data here if collision
        * @return True if collision.
        */
        virtual bool collide(const Collider* collider,CollisionData& data) const = 0;

        //Collision detectors
        /**
       * Check collision with a sphere
       * @param collider sphere to check collision with
       * @param data Put collision data here if collision
       * @return True if collision
       */
        virtual bool collide(const SphereCollider& collider, CollisionData& data) const = 0;


        /**
             * Check collision with a box
             * @param collider Box to check collision with
             * @param data Put collision data here if collision
             * @return True if collision
             */
        virtual bool collide(const BoxCollider& collider, CollisionData& data) const = 0;


        /**
             * Check collision with a capsule
             * @param collider Box to check collision with
             * @param data Put collision data here if collision
             * @return True if collision
             */
        virtual bool collide(const CapsuleCollider& collider, CollisionData& data) const = 0;

    };

    /**
     * Potential collision helper struct
     */
    struct PotentialCollision {
        /**
         * Store a potential collision between two objects
         * Only one combination of the objects needs to be registered (a-b OR b-a)
         */
        PotentialCollision(Collideable* a, Collideable* b) : a(a), b(b){}

        /**
         * Get the potential collision entry that is different but equivalent
         * Used to remove duplicate collisions
         */
        PotentialCollision getEquivalent() const {
            return {b,a};
        }


        /**
         * Check if two PotentialCollisions are equal
         * Make sure to also check with getEquivalent()
         * Used to remove duplicates
         */
        bool operator==(const PotentialCollision &rhs) const {
            return a == rhs.a &&
                   b == rhs.b;
        }

        Collideable* a;
        Collideable* b;
    };

} // Doge
