//
// Created by Philip on 1/7/2023.
//

#pragma once

namespace Doge {

    //Will be passed into render application to be updated on its callbacks.
    //Can also be used as an interface for libraries like ray-lib,which already use this type of input system
    //Also makes key mapping easier.
    //Then it can be passed into a scene to be queried
    //API independent, and doesn't need 700 callbacks
    class InputManager {
        //isKeyDown(key_id)

    };

} // Doge
