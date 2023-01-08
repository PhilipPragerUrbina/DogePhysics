//
// Created by Philip on 1/7/2023.
//

#pragma once

#include "../GameObject.hpp"

namespace Doge {

    /**
     * Empty Game object
     * Just acts as a 3d transformation or for grouping
     */
    class Empty : public GameObject{
    protected:
        void render(Renderer *renderer) override {}
        void update(real delta_time) override {}
    };

} // Doge
