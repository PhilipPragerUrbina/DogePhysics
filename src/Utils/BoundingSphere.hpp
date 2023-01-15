//
// Created by Philip on 1/12/2023.
//

#pragma once

#include "Vector3.hpp"

namespace Doge {

    /**
     * Sphere bounding "box" with overlap detection
     */
    class BoundingSphere {
    public:

        Vector3 position;
        real radius;

        /**
         * Create a spherical bounding box
         * @param position Position in world
         * @param radius Radius of sphere
         */
        BoundingSphere(const Vector3& position, real radius) : position(position), radius(radius){}

        /**
         * Check if two spheres intersect
         * @return True if intersect
         */
        bool checkOverlap(const BoundingSphere& other) const {
            real radii_sum = other.radius + radius; //Get sum of radii
            return position.distance(other.position) < radii_sum; //Is less than distance
        }

        /**
         * Check if point is within sphere
         * @return True if within
         */
        bool isPointWithin(const Vector3& point) const {
            return point.distance(position) < radius;
        }

    };

} // Doge
