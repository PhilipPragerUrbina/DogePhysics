//
// Created by Philip on 1/9/2023.
//

#pragma once

#include "real.hpp"

namespace Doge {

    /**
     * 3x3 Matrix used for inertia tensors
     */
    class Matrix3 {
    public:
        real data[9];

    };
    /**
     * Alternative naming
     */
    typedef Matrix3 Mat3;

} // Doge
