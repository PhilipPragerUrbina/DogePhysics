//
// Created by Philip on 12/26/2022.
//

#pragma once

#include <cmath>
#include <ostream>
#include "real.hpp"

namespace Doge {

    /**
     * A 3d vector
     */
    class Vector3 {
    public:
        real x,y,z; // Coordinate values

        /**
         * Create a zero initialized vector
         */
        Vector3() : x(0) , y(0), z(0){};

        /**
         * Create a vector from 3 components
         * @param x X component
         * @param y Y component
         * @param z Z component
         */
        Vector3(const real& x,const real& y,const real& z) : x(x),y(y),z(z){};

        /**
         * Create a vector from a scalar value
         * @param scalar All components will be set to this value
         */
        Vector3(const real& scalar) : x(scalar) , y(scalar), z(scalar){};

        /**
         * Copy constructor
         */
         Vector3(const Vector3& other) : Vector3(other.x,other.y,other.z){}

         /**
          * Assign one vector's components to another
          */
         Vector3& operator= (const Vector3& other){
            if(&other != this){ //check self assignment
                x = other.x;
                y = other.y;
                z = other.z;
            }
            return *this;
        }

        /**
         * Negate a vector(Make all components negative)
         * @return Inverted/negated vector
         */
        inline Vector3 operator-() const{
            return {-x, -y, -z};
        }

        /**
         * Add the components of two vectors
         * @return The sum
         */
        friend Vector3 inline operator+(const Vector3& a, const Vector3& b){
            return {a.x+b.x, a.y+b.y, a.z+b.z};
        }
        /**
         * Subtract the components of two vectors
         * @return The subtracted vector
         */
        friend Vector3 inline operator-(const Vector3& a, const Vector3& b){
            return {a.x-b.x, a.y-b.y, a.z-b.z};
        }
        /**
         * Multiply the components of two vectors
         * @return The component product
         */
        friend Vector3 inline operator*(const Vector3& a, const Vector3& b){
            return {a.x*b.x, a.y*b.y, a.z*b.z};
        }
        /**
         * Divide the components of two vectors
         * The divided vector
         */
        friend Vector3 inline operator/(const Vector3& a, const Vector3& b){
            return {a.x/b.x, a.y/b.y, a.z/b.z};
        }

        void inline operator+=(const Vector3& other){
            *this = *this + other;
        }
        void inline operator-=(const Vector3& other){
            *this = *this - other;
        }
        void inline operator*=(const Vector3& other){
            *this = *this * other;
        }
        void inline operator/=(const Vector3& other){
            *this = *this / other;
        }

        /**
         * Get the length of a vector squared(without the square root)
         * Good for performance in some cases, where only relative length matters
         */
        inline real lengthSquared() const{
            return x*x + y*y + z*z;
        }
        /**
         * Get the length or magnitude of a vector
         */
        inline real length()const {
            return sqrt(lengthSquared());
        }

        /**
         * Get the distance between this vector and another
         */
        real distance(const Vector3& b) const{
            return (*this-b).length();
        }
        /**
         * Get the distance between this vector and another squared(without square root)
         * Good for performance in some cases, where only relative distance matters
         */
        real distanceSquared(const Vector3& b) const{
            return (*this-b).lengthSquared();
        }

        /**
         * Get the normalized vector
         * @return The unit vector
         */
        inline Vector3 normalized() const{
            return *this/length();
        }

        /**
         * Get the dot product of two vectors
         * @return The scalar product
         */
        real dot(const Vector3& b) const {
            return x*b.x + y*b.y + z*b.z;
        }

        /**
         * Used to print vector to console
         */
        friend std::ostream &operator<<(std::ostream &os, const Vector3 &vector) {
            os << "(" << vector.x << "," << vector.y << "," << vector.z << ")";
            return os;
        }

        /**
         * Get the absolute value of each of the vector's components
         */
        Vector3 abs() const{
            return {std::abs(x), std::abs(y), std::abs(z)};
        }

        /**
         * Get the perpendicular vector to two other vectors
         * @remember The right-hand rule
         * @return The cross product or vector product
         */
        Vector3 cross(const Vector3 &other) const {
            return {y * other.z - z * other.y,
                    z * other.x - x * other.z,
                    x * other.y - y * other.x};
        }
        /**
         * Reflect a vector over a normal
         * @param n The normalized direction normal
         * @return The reflected vector
         */
        Vector3 reflect(const Vector3& n) const{
            return *this - 2*this->dot(n) * n;
        }

    };

    /**
     * Make it simpler to use shader code
     * Alternative name for Vector3
     */
    typedef Vector3 Vec3;

} // Doge
