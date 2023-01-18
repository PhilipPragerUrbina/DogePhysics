//
// Created by Philip on 1/9/2023.
//

#pragma once

#include <cmath>
#include "real.hpp"
#include "Vector3.hpp"
#include "Matrix3.hpp"

namespace Doge {

    /**
     * Represents 3 DOF rotation
     * @authors Based on code from Ian Millington and Stanford(https://cs.stanford.edu/~acoates/quaternion.h)
     */
    class Quaternion {
    public:
        real i,j,k,r; //Also known as x y z w

        /**
        * Zero rotation.
        */
        Quaternion() : r(1), i(0), j(0), k(0) {}

        /**
         * Create a quaternion
         * @param i,j,k Complex components
         * @param r Real component
         */
        Quaternion(real i, real j, real k, real r) : i(i), j(j), k(k), r(r){}

        /**
         * Get magnitude or norm of quaternion
         */
        real magnitude() const { return sqrt(i*i+j*j+k*k+r*r); }

        /**
         * Normalize the quaternion
         * Used to reduce rounding errors
         */
        void normalize() {
            real length = r*r + i*i + j*j + k*k;
            if(length == 0.0){ //Make sure it is non-zero
                r = 1; //Use no rotation quaternion
                return;
            }
            //normalize
            length = sqrt(length);
            i /= length;
            j /= length;
            k /= length;
            r /= length;
        }

        /**
         * Get conjugate of quaternion
         */
        Quaternion conjugate() const {
            return {-i,-j,-k, r};
        }

        /**
         * General inverse of quaternion
         */
        Quaternion inverse() const {
            real length = magnitude();
            if(length == 0.0){
                return {0,0,0,1};
            }
            return conjugate() * (1/length);
        }

        /**
         * Multiply all components of quaternion by a scalar and return the product
         */
        Quaternion operator*(real scalar) const {
            return {i * scalar, j * scalar, k* scalar, r * scalar};
        }

        /**
         * Combine quaternions
         * @param b What to multiply by
         */
        void operator *=(const Quaternion &b)
        {
            r = r * b.r - i * b.i -
                j * b.j - k * b.k;
            i = r * b.i + i * b.r +
                j * b.k - k * b.j;
            j = r * b.j + j * b.r +
                k * b.i - i * b.k;
            k = r * b.k + k * b.r +
                i * b.j - j * b.i;
        }


        /**
         * Adds vector to quaternion
         * Can be used to update quaternions orientation
         * Applies 1/2 and quaternion multiplication for you(automatic conversion)
         * Equivalent to q += 1/2[v.x,v.y,v.z,0]q
         * @param vector Vector to add
         * @param multiplier Additional multiplier to multiply along with 1/2
         */
        void addVector (const Vector3& vector, real multiplier = 1.0){
            Quaternion q(vector.x ,vector.y,vector.z,0 );
            q *= *this;
            r += q.r * ((real)0.5) * multiplier;
            i += q.i * ((real)0.5) * multiplier;
            j += q.j * ((real)0.5) * multiplier;
            k += q.k * ((real)0.5) * multiplier;
        }




        /**
        * Get corresponding rotation matrix
        */
        Matrix3 getOrientation() const
        {
            Matrix3 out{};
            out.data[0][0] = 1 - (2*j*j + 2*k*k);
            out.data[0][1] = 2*i*j + 2*k*r;
            out.data[0][2] = 2*i*k - 2*j*r;
            out.data[1][0] = 2*i*j - 2*k*r;
            out.data[1][1] = 1 - (2*i*i  + 2*k*k);
            out.data[1][2] = 2*j*k + 2*i*r;
            out.data[2][0] = 2*i*k + 2*j*r;
            out.data[2][1] = 2*j*k - 2*i*r;
            out.data[2][2] = 1 - (2*i*i  + 2*j*j);
            return out;
        }



    };

} // Doge
