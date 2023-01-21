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
        std::vector<CollisionData> data;
        void solve(const real &sub_step_delta) override {
            data = layer->checkCollisions();
            for (const CollisionData& collision : data) {
                RigidBody* a = (RigidBody *)(collision.a);
                RigidBody* b = (RigidBody *)(collision.b);

                Vector3 r1= a->transformPoint(collision.position)  ; //todo are these the two separate contact points, or just one of them. Position vs r1, r2
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



            //vecloty solve
            //it is a little early but it is fine, since it does not really care too much(Only updates velcotites of these objects which have already been updated)
            //If there are problems mabye move it to seperate loop or try to re-check contacts collisions
            for (const CollisionData& collision : data) {
                RigidBody *a = (RigidBody *) (collision.a);
                RigidBody *b = (RigidBody *) (collision.b);

                //todo friction and two separate vn and vn hat
                Vector3 vn1 = collision.normal * a->getVelocity();
                Vector3 vn2 = collision.normal * b->getVelocity();

                real e = 0.01; //Restitution coefficient

                //todo e=0 jittering check
                Vector3 delta_v1 = collision.normal*(-vn1 +(-e*vn1).min(0));
                Vector3 delta_v2 = collision.normal*(-vn2 +(-e*vn2).min(0));

                a->setVelocity(a->getVelocity() + delta_v1);
                b->setVelocity(b->getVelocity() + delta_v2);



            }

        }

    };

} // Doge
