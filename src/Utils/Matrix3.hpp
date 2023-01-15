//
// Created by Philip on 1/9/2023.
//

#pragma once

#include "real.hpp"
#include "Vector3.hpp"

namespace Doge {

    /**
     * 3x3 Matrix used for inertia tensors
     */
    class Matrix3 {
    public:
        real data[3][3]; // X = row(down++), Y = Column(Right++)

        /**
         * Post multiplies with vector(column)
         * @param v 3d Vector to multiply with
         * @return Vector product
         */
        Vector3 operator * (const Vector3& v) const {
            return {
                data[0][0]*v.x + data[0][1]*v.y + data[0][2] * v.z, //First row
                data[1][0]*v.x + data[1][1]*v.y + data[1][2] * v.z,
                data[2][0]*v.x + data[2][1]*v.y + data[2][2] * v.z
            };
        }

        /**
         * Pre multiply a vector with this matrix by transposing the vector first
         * @param v Vector to transpose and pre-multiply. Would go first in the equation, and usually have a T superscript.
         * @return Vector product
         * @see operator * for post multiply
         */
        Vector3 preMultiply(const Vector3& v) const {
            return {
                    data[0][0]*v.x + data[1][0]*v.y + data[2][0] * v.z, //First row
                    data[0][1]*v.x + data[1][1]*v.y + data[2][1] * v.z,
                    data[0][2]*v.x + data[1][2]*v.y + data[2][2] * v.z
            };
        }

        /**
         * Multiply two matrices
         * @param b Other Matrix
         * @return 3x3 Product
         * @author Uses https://stackoverflow.com/questions/41018065/multiplying-3x3-matrices-in-c
         */
        Matrix3 operator * (const Matrix3& b) const {
            Matrix3 out{};
            for (int i = 0; i < 3; i++){
                for (int j = 0; j < 3; j++) {
                    for (int u = 0; u < 3; u++){
                        out.data[i][j] += data[i][u] * b.data[u][j];
                    }
                }
            }
            return out;
        }

        /**
         * Get the inverse of the 3x3 matrix
         * @return Inverse matrix, or just the matrix if the determinant is 0
         * @author Modified code from Ian Millington
         */
        Matrix3 inverse() const {
            Matrix3 out{};
            real t4 = data[0][0]*data[1][1];
            real t6 = data[0][0]*data[1][2];
            real t8 = data[0][1]*data[1][0];
            real t10 = data[0][2]*data[1][0];
            real t12 = data[0][1]*data[2][0];
            real t14 = data[0][2]*data[2][0];

            // Calculate the determinant
            real t16 = (t4*data[2][2] - t6*data[2][1] - t8*data[2][2]+
                        t10*data[2][1] + t12*data[1][2] - t14*data[1][1]);

            // Make sure the determinant is non-zero.
            if (t16 == 0.0) {return *this;};
            real t17 = 1/t16;

            out.data[0][0] = (data[1][1]*data[2][2]-data[1][2]*data[2][1])*t17;
            out.data[0][1] = -(data[0][1]*data[2][2]-data[0][2]*data[2][1])*t17;
            out.data[0][2] = (data[0][1]*data[1][2]-data[0][2]*data[1][1])*t17;
            out.data[1][0] = -(data[1][0]*data[2][2]-data[1][2]*data[2][0])*t17;
            out.data[1][1] = (data[0][0]*data[2][2]-t14)*t17;
            out.data[1][2] = -(t6-t10)*t17;
            out.data[2][0] = (data[1][0]*data[2][1]-data[1][1]*data[2][0])*t17;
            out.data[2][1] = -(data[0][0]*data[2][1]-t12)*t17;
            out.data[2][2] = (t4-t8)*t17;
            return out;
        }

        /**
         * Get a transpose of the matrix
         * @return Transposed matrix
         * Rows and columns are swapped
         * Useful for getting faster inverse of rotations
         */
        Matrix3 transposed() const {
            Matrix3 out{};
            for (int i = 0; i < 3; i++){
                for (int j = 0; j < 3; j++) {
                    out.data[i][j] = data[j][i];
                }
            }
            return out;
        }






    };
    /**
     * Alternative naming
     */
    typedef Matrix3 Mat3;

} // Doge
