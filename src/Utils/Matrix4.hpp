//
// Created by Philip on 12/26/2022.
//

#pragma once

#include "real.hpp"

namespace Doge {
    /**
     * A 4x4 transformation Matrix
     */
    class Matrix4 {
        real data[12];


    };
    /**
     * Alternative names for matrix.
     */
    typedef Matrix4 Transform;
    typedef Matrix4 Mat4;
} // Doge
