//
// Created by Philip on 1/10/2023.
//

#pragma once

#include <memory>
#include "../Constraint.hpp"
#include "../../Objects/XPBD/Constrainable.hpp"

namespace Doge {

    /**
     * Simple distance constraint
     * Two objects must stay within certain distance
     */
    class DistanceConstraint : public Constraint{
    private:
        //todo make sure memory is not trapped
        //Objects
        std::shared_ptr<Constrainable> a;
        std::shared_ptr<Constrainable> b;

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
        DistanceConstraint( std::shared_ptr<Constrainable> a, std::shared_ptr<Constrainable> b , const real rest_distance, const real inverse_stiffness = 0) : a(a),b(b), rest_distance(rest_distance), inverse_stiffness(inverse_stiffness){};

        void init() override {} //no init

        void beforeSolve(const real &sub_step_delta, int sub_step_idx) override {
            //update objects
            a->beforeSolve(sub_step_delta,sub_step_idx);
            b->beforeSolve(sub_step_delta,sub_step_idx);
        }

        void solve(const real &sub_step_delta ) override {
            real distance = a->getPosition().distance(b->getPosition());
            Vector3 a_to_b = (b->getPosition() - a->getPosition()).normalized(); //X1 to X2 normalized

            //Denominator of constraint function
            real denominator = a->getInverseMass()+b->getInverseMass() + (inverse_stiffness / (sub_step_delta * sub_step_delta)); //Also add compliance using timestamp squared

            //distribute error based on inverse masses to get correction vectors
            Vector3 correction_a = (a->getInverseMass()/(denominator))*(distance - rest_distance)*a_to_b;
            Vector3 correction_b = -(b->getInverseMass()/(denominator))*(distance - rest_distance)*a_to_b;

            //correct position
            a->setPosition(a->getPosition() + correction_a);
            b->setPosition(b->getPosition() + correction_b);
            //https://www.youtube.com/watch?v=RhEkKDEQEYM

        }

        void afterSolve(const real &sub_step_delta, int sub_step_idx) override {
            a->afterSolve(sub_step_delta,sub_step_idx);
            b->afterSolve(sub_step_delta,sub_step_idx);
        }


    };

} // Doge
