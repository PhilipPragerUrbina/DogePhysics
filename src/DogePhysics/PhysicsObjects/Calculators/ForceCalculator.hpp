//
// Created by Philip on 12/30/2022.
//

#pragma once

#include "../Particles/Particle.hpp"

namespace Doge {

    /**
     * Interface for very simple physical operation on an object
     */
    class ForceCalculator {
        virtual void apply(Particle& particle){
            //todo switch to forceable physics object(unless collider is needed for surface area)
        }
    };

} // Doge
