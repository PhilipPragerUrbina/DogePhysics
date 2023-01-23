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

        void init(double delta_time) override {


            layer->findPotentialCollisions(delta_time);

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

                Vector3 r1= a->transformPoint(collision.r2)  ; //it is a single contact point
                Vector3 r2 = b->transformPoint(collision.r2); //todo doc what data r1 and r2 represent


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



            //velocity solve
            //it is a little early but it is fine, since it does not really care too much(Only updates velcotites of these objects which have already been updated)
            //If there are problems mabye move it to seperate loop or try to re-check contacts collisions
            for (const CollisionData& collision : data) {
                //Get bodies
                RigidBody *a = (RigidBody *) (collision.a);
                RigidBody *b = (RigidBody *) (collision.b);

                //todo still some slight funkiness with r1 and r2. Is it just r2 and r2. Is it r1 and r2. is it r2 and r1

                //Get r1 and r2
                Vector3 r1= a->transformPoint(collision.r2)  ;
                Vector3 r2 = b->transformPoint(collision.r2);
                //Get collision normal
                Vector3 n = collision.normal; //todo swap if not working properly
                //get velocities todo optimize
                Vector3 v1 = a->getVelocity(); //Just for readability
                Vector3 v2 = b->getVelocity();
                Vector3 w1 = a->getAngularVelocity();
                Vector3 w2 = b->getAngularVelocity();
                Vector3 wmass1 = a->getInverseMass() + a->getInverseIntertia().preMultiply(r1.cross(n)) * (r1.cross(n)); //Compute generalized masses
                Vector3 wmass2 = b->getInverseMass() + b->getInverseIntertia().preMultiply(r2.cross(n)) * (r2.cross(n)); //todo optimize(Computed twice)
                //Compute normal and tangential velocities
                Vector3 v = (v1+w1.cross(r1))-(v2+w2.cross(r2));
                Vector3 vn = n * v;
                Vector3 vt = v - n*vn;
                //Compute pre update
                Vector3 vhat = (a->getPreUpdateVelocities() + a->getPreUpdateAngularVelocities().cross(r1)) - (b->getPreUpdateVelocities() + b->getPreUpdateAngularVelocities().cross(r2));
                Vector3 vnhat = n * vhat;

                //todo put friction and restitution variables as properties

                //Compute friction force
                //todo friction force
                //Vector3 vdelta = -vt.normalized()*fmin(0, vt.length());

                //todo damping

                //Apply restitution
                real e = 0.01; //Restitution coefficient
                Vector3 vdelta = n*(-vn+(-e*vnhat).min(0));
                //todo jitter check

                Vector3 p = vdelta/(wmass1+wmass2);
                a->setVelocity(a->getVelocity() + p * a->getInverseMass());
                b->setVelocity(b->getVelocity() - p * b->getInverseMass());

                a->setAngularVelocity(a->getAngularVelocity() + a->getInverseIntertia() * (r1.cross(p)));
                b->setAngularVelocity(b->getAngularVelocity() - b->getInverseIntertia() * (r2.cross(p)));



            }

        }

    };

} // Doge
