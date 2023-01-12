//
// Created by Philip on 12/30/2022.
//

#pragma once

#include <iostream>
#include "../../Utils/real.hpp"
#include "../Objects/Physical.hpp"

namespace Doge {

    class SimpleDrag {
    private:
        Vector3 last;
        real k1;
        real k2;
    public:
        SimpleDrag(real k1) : k1(k1),k2(0.0001){}

        //todo finish
        void apply(Physical* particle){
            particle->applyForce(-last); //undo last to avoid compound force todo better solution
            Vector3 force = particle->getVelocity();
            real drag = force.length();
            drag = 0.9;

            force = force.normalized();

            force*=-drag;

            particle->applyForce(force);
            last = force;
        }

    };

} // Doge
