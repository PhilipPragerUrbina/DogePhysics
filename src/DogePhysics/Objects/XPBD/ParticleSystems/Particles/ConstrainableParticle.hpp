//
// Created by Philip on 1/9/2023.
//

#pragma once

#include "../../Constrainable.hpp"

namespace Doge {

    /**
     * XPBD particle
     */
    class ConstrainableParticle : public Constrainable{
    private:
        Vector3 prev_position;
    public:

        ConstrainableParticle(real mass) : Constrainable(mass){}

        void beforeSolveIntegrate(const real &sub_step_delta) override {
            //Corresponds to first "for n particles" loop
            prev_position = position; //Store last position
            velocity += sub_step_delta * net_force * getInverseMass(); //update velocity with external forces
            position += sub_step_delta * velocity; //update position
        }

        void afterSolveIntegrate(const real &sub_step_delta) override {

            //Corresponds to second "for n particles" loop
            velocity = (position - prev_position)/sub_step_delta; //Update velocity after constrains

        }

    };

} // Doge
