//
// Created by Philip on 1/10/2023.
//

#pragma once

#include <memory>
#include "../Constraint.hpp"
#include "../../Objects/XPBD/Constrainable.hpp"
#include "../../Objects/XPBD/RigidBody.hpp"

namespace Doge {

    /**
     * Simple distance constraint
     * Two objects must stay within certain distance
     */
    class DistanceConstraintRigid : public Constraint{
    private:
        //todo make sure memory is not trapped
        //Objects
        std::shared_ptr<RigidBody> a;
        std::shared_ptr<RigidBody> b;

        //options
        const real rest_distance;
        const real inverse_stiffness;
    public:

        /**
         * Create a distance constraint between two objects.
         * @param a First object
         * @param b Second object
         * @param rest_distance Distance to hold between objects
         * @param inverse_stiffness (1/stiffness). How much to enforce the constraint, also known as compliance.
         * Examples: 0 is perfectly rigid hard constraint, 0.001 is a pretty stretchy constraint.
         */
        DistanceConstraintRigid( std::shared_ptr<RigidBody> a, std::shared_ptr<RigidBody> b , const real rest_distance, const real inverse_stiffness = 0) : a(a),b(b), rest_distance(rest_distance), inverse_stiffness(inverse_stiffness){};

        void init() override {} //no init

        void beforeSolve(const real &sub_step_delta, int sub_step_idx) override {
            //update objects
            a->beforeSolve(sub_step_delta,sub_step_idx);
            b->beforeSolve(sub_step_delta,sub_step_idx);
        }

        void solve(const real &sub_step_delta ) override {
            Vector3 r1= {0,0,0}; //Attachment locations in world coordinates
            Vector3 r2 = {0.5,0.6,0}; //todo is this global or local. Does it need to be rotated

            Vector3 n = (b->getPosition() - a->getPosition()).normalized(); //X1 to X2 normalized. Correction direction
            real C = rest_distance-( (a->getPosition()).distance(b->getPosition()) ); //Constraint attachment point distance. Distance - rest distance
            //todo Does distance depend on r1 or r2


            Vector3 w1 = a->getInverseMass() + a->getInverseIntertia().preMultiply(r1.cross(n)) * (r1.cross(n)); //Compute generalized masses todo check order of operations
            Vector3 w2 = b->getInverseMass() + b->getInverseIntertia().preMultiply(r2.cross(n)) * (r2.cross(n));

            Vector3 lambda = (-C)/(w1+w2); //Compute Lagrange multiplier

            a->setPosition(a->getPosition() + lambda*n*a->getInverseMass()); //update states
            b->setPosition(b->getPosition() -lambda*n*b->getInverseMass()); //Negative

            Quaternion new_rotation1 = a->getRotation();
            new_rotation1.addVector(a->getInverseIntertia() * (r1.cross(lambda*n))); //add vector and multiply by lambda/  a->setRotation(new_rotation1); //update values
            a->setRotation(new_rotation1);

            Quaternion new_rotation2 = b->getRotation();
            new_rotation2.addVector(-(b->getInverseIntertia() * (r2.cross(lambda*n)))); //add vector and multiply by lambda. Also make negative.
            b->setRotation(new_rotation2); //update values


            //https://www.youtube.com/watch?v=RhEkKDEQEYM

        }

        void afterSolve(const real &sub_step_delta, int sub_step_idx) override {
            a->afterSolve(sub_step_delta,sub_step_idx);
            b->afterSolve(sub_step_delta,sub_step_idx);
        }


    };

} // Doge
