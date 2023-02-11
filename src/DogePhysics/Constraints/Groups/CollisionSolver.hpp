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
            for ( CollisionData& collision : data) {
                RigidBody* a = (RigidBody *)(collision.a);
                RigidBody* b = (RigidBody *)(collision.b);

                Vector3 r1= ( collision.r1 ) ; //it is a single contact point
                Vector3 r2 = (collision.r2 ); //todo doc what data r1 and r2 represent
                 //todo doc that it is tranformed by collider


                Vector3 n = collision.normal;
                real C = collision.depth;

                Vector3 w1 = a->getInverseMass() + r1.cross(n).dot(a->getInverseIntertiaLocal() * r1.cross(n)); //Compute generalized masses
                Vector3 w2 = b->getInverseMass() +  r2.cross(n).dot(b->getInverseIntertiaLocal() * r2.cross(n));

                Vector3 lambda = (-C)/(w1+w2+(inverse_stiffness / (sub_step_delta * sub_step_delta))); //Compute Lagrange multiplier
                collision.lambda = lambda; //todo doc

                a->setPosition(a->getPosition() + lambda*n*a->getInverseMass()); //update states
                b->setPosition(b->getPosition() -lambda*n*b->getInverseMass()); //Negative

                Quaternion new_rotation1 = a->getRotation();
                new_rotation1.addVector(a->getInverseIntertiaRotated() * (r1.cross(lambda*n)),1); //add vector and multiply by lambda/  a->setRotation(new_rotation1); //update values
                a->setRotation(new_rotation1);

                Quaternion new_rotation2 = b->getRotation();
                new_rotation2.addVector((b->getInverseIntertiaRotated() * (r2.cross(lambda*n))), -1); //add vector and multiply by lambda. Also make negative.
               b->setRotation(new_rotation2); //update values

                //todo static friction


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



                //Get r1 and r2
                Vector3 r1= (collision.r1 );
                Vector3 r2 = (collision.r2 );
                //Get collision normal
                Vector3 n = collision.normal;
                //get velocities todo optimize
                Vector3 v1 = a->getVelocity(); //Just for readability
                Vector3 v2 = b->getVelocity();
                Vector3 w1 = a->getAngularVelocity();
                Vector3 w2 = b->getAngularVelocity();
                // The line below is equivalent to Eq (2) because the component-wise multiplication of a transposed vector and another vector is equal to the dot product of the two vectors.
                Vector3 wmass1 =a->getInverseMass() + r1.cross(n).dot(a->getInverseIntertiaRotated() * r1.cross(n)); //Compute generalized masses
                Vector3 wmass2 = b->getInverseMass() + r2.cross(n).dot(b->getInverseIntertiaRotated() * r2.cross(n)); //todo check if this is local or rotated. https://github.com/Jondolf/bevy_xpbd/blob/main/src/systems.rs
                //Compute normal and tangential velocities
                Vector3 v = (v1+w1.cross(r1))-(v2+w2.cross(r2));
                real vn = n.dot(v);
                Vector3 vt = v - n*vn;
                //Compute pre update
                Vector3 vhat = (a->getPreUpdateVelocities() + a->getPreUpdateAngularVelocities().cross(r1)) - (b->getPreUpdateVelocities() + b->getPreUpdateAngularVelocities().cross(r2));
                real vnhat = n.dot(vhat);

                //todo put friction and restitution variables as properties

                //Compute friction force
                real ud =0.1; //dynamic friction coefficient
                real lambdan = collision.lambda.x; //Normal forces
                real fn = lambdan / (sub_step_delta * sub_step_delta);
                Vector3 vdelta = -vt.normalized()*fmin(sub_step_delta * ud * abs(fn), vt.length());

                //todo restitution causes structure to bounce apart. Also why spin with no friction.

                //todo damping

                //Apply restitution
                real e =0.01; //Restitution coefficient
                vdelta += n*(-vn+fmin(-e*vnhat,0));
                //todo jitter check

                Vector3 p = vdelta/(wmass1+wmass2);
                a->setVelocity(a->getVelocity() + p * a->getInverseMass());
                b->setVelocity(b->getVelocity() - p * b->getInverseMass());

               a->setAngularVelocity(a->getAngularVelocity() + a->getInverseIntertiaRotated() * (r1.cross(p)));
             b->setAngularVelocity(b->getAngularVelocity() - b->getInverseIntertiaRotated() * (r2.cross(p)));



            }

        }

    };

} // Doge
