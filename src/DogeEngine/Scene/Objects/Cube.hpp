//
// Created by Philip on 1/7/2023.
//

#pragma once

#include <iostream>
#include "../GameObject.hpp"

namespace Doge {

    /**
     * A basic cube or rectangular prism
     */
    class Cube : public GameObject{
        void render(Renderer *renderer) override{
            renderer->drawCube();
        }

        void update(real delta_time) override{}
    };

} // Doge
