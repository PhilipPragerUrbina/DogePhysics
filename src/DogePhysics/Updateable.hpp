//
// Created by Philip on 1/9/2023.
//

#pragma once

#include "../Utils/real.hpp"

namespace Doge {

    /**
     * An object that needs to be updated/stepped every update cycle.
     */
    class Updateable {
    public:
        /**
         * Step the simulation forward
         * @param delta_time Time since last update
         */
        virtual void step(real delta_time) = 0;
    };

} // Doge
