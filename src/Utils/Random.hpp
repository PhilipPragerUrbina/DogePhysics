//
// Created by Philip on 12/28/2022.
//

#pragma once

#include "Vector3.hpp"

namespace Doge {

    /**
     * Utility class for generating random numbers
     */
    class Random {
    public:
        /**
          * Generate a vector with random components in a range
          * @param min Minimum value(inclusive)
          * @param max Maximum value(exclusive)
          * @return Random vector using rand()
          */
        static Vector3 randomVector(real min, real max){
            return {randomReal(min,max),randomReal(min,max),randomReal(min,max)};
        }

        /**
        * Generate a vector with random components in a vector range
        * @param min Minimum value(inclusive)
        * @param max Maximum value(exclusive)
        * @return Random vector using rand()
        */
        static Vector3 randomVector(const Vector3& min, const Vector3& max){
            return {randomReal(min.x,max.x),randomReal(min.y,max.y),randomReal(min.z,max.z)};
        }

        /**
         * Generate a random real between two numbers
         * @param min Minimum value(inclusive)
         * @param max Maximum value(exclusive)
         * @return Random real using rand()
         */
        static real randomReal(real min, real max) {
            return min + (((real) ::rand()) / (real) RAND_MAX) * (max-min);
        }

    };

} // Doge
