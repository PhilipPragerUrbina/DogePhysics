//
// Created by Philip on 1/9/2023.
//

#pragma once

#include "../../Objects/XPBD/RigidBody.hpp"
#include "../../Group.hpp"
#include "../Constraint.hpp"
#include "../../Collisions/Layers/CollisionLayer.hpp"

namespace Doge {

    class CollisionSolver : public Constraint{
    private:
        std::shared_ptr<CollisionLayer> layer;
        const real inverse_stiffness;
    public:
        CollisionSolver( std::shared_ptr<CollisionLayer> layer, const real inverse_stiffness = 0 ) : layer(layer), inverse_stiffness(inverse_stiffness){

        }

        void init() override {


            layer->findPotentialCollisions();

        }

        void beforeSolve(const real &sub_step_delta, int sub_step_idx) override {

            for (const std::shared_ptr<Collideable>& collideable : *layer->getContents()) {
                auto* rigid_body = (RigidBody *)(collideable.get());
                rigid_body->beforeSolve(sub_step_delta,sub_step_idx);
            }


        }

        void solve(const real &sub_step_delta) override {
            std::vector<CollisionData> data = layer->checkCollisions();
            for (const CollisionData& collision : data) {
                RigidBody* a = (RigidBody *)(collision.a);
                RigidBody* b = (RigidBody *)(collision.b);

                Vector3 r1= a->transformPoint(collision.position)  ;
                Vector3 r2 = b->transformPoint(collision.position);


                Vector3 n = collision.normal;
                real C = collision.depth;

                Vector3 w1 = a->getInverseMass() + a->getInverseIntertia().preMultiply(r1.cross(n)) * (r1.cross(n)); //Compute generalized masses
                Vector3 w2 = b->getInverseMass() + b->getInverseIntertia().preMultiply(r2.cross(n)) * (r2.cross(n));

                Vector3 lambda = (-C)/(w1+w2+(inverse_stiffness / (sub_step_delta * sub_step_delta))); //Compute Lagrange multiplier

                a->setPosition(a->getPosition() + lambda*n*a->getInverseMass()); //update states
                b->setPosition(b->getPosition() -lambda*n*b->getInverseMass()); //Negative

                Quaternion new_rotation1 = a->getRotation();
                new_rotation1.addVector(a->getInverseIntertia() * (r1.cross(lambda*n))); //add vector and multiply by lambda/  a->setRotation(new_rotation1); //update values
                a->setRotation(new_rotation1);

                Quaternion new_rotation2 = b->getRotation();
                new_rotation2.addVector(-(b->getInverseIntertia() * (r2.cross(lambda*n)))); //add vector and multiply by lambda. Also make negative.
                b->setRotation(new_rotation2); //update values

            }
        }

        void afterSolve(const real &sub_step_delta, int sub_step_idx) override {
            for (const std::shared_ptr<Collideable>& collideable : *layer->getContents()) {
                auto* rigid_body = (RigidBody *)(collideable.get());
                rigid_body->afterSolve(sub_step_delta,sub_step_idx);
            }
        }

    };

} // Doge
