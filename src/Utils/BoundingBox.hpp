//
// Created by Philip on 1/12/2023.
//

#pragma once

#include "Vector3.hpp"

namespace Doge {

    /**
     * Axis aligned bounding box
     */
    class BoundingBox {
    private:
        Vector3 min,max;
    public:
        /**
         * Create bounding box from two points
         * Do not have to be min and max
         */
        BoundingBox(const Vector3& a, const Vector3& b){
            min = a.min(b);
            max = a.max(b);
        }

        /**
         * Expand bounding box to contain position
         */
        void expand(const Vector3& position){
            min = min.min(position);
            max = max.max(position);
        }

        /**
         * Get minimum position of bounding box
         */
        Vector3 getMin() const {
            return min;
        }

        /**
         * Get maximum position of bounding box
         */
        Vector3 getMax() const {
            return max;
        }
    };

} // Doge
