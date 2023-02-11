//
// Created by Philip on 1/9/2023.
//

#pragma once


#include <algorithm>
#include "Collider.hpp"

namespace Doge {

    /**
     * Capsule primitive collider
     */
class CapsuleCollider : public Collider{
    private:
    real length;
    real radius;
    BoundingSphere bounding;
    Transformable* transform;

    public:

    /**
     *
     * @param length Length of middle
     * @param radius Radius of spheres at end and tube
     */
    CapsuleCollider(real length, real radius) : length(length) ,radius(radius), bounding(0,0){
        bounding.radius = length/2.0 + radius ;
    }

        /**
         * Collide with any other object by passing self
         */
       bool collide(const Collider *collider, CollisionData &data) const override {
            return collider->collide(*this,data);
       }

    void setParentTransform( Transformable *parent_transform) override {
           bounding.position = parent_transform->getPosition();
        transform = parent_transform;
    }

    BoundingSphere getBounding() const override {
        return bounding;
    }

    Matrix3 createInertiaTensor(real mass) const override {
        Doge::Matrix3 mat{};
        //todo estimated newton box tensor vs exact tensor below

        const real height = length;
        const real radiusSquare = radius * radius;
        const real heightSquare = height * height;
        const real radiusSquareDouble = radiusSquare + radiusSquare;
        const real factor1 = real(2.0) * radius / (real(4.0) * radius + real(3.0) * height);
        const real factor2 = real(3.0) * height / (real(4.0) * radius + real(3.0) * height);
        const real sum1 = real(0.4) * radiusSquareDouble;
        const real sum2 = real(0.75) * height * radius + real(0.5) * heightSquare;
        const real sum3 = real(0.25) * radiusSquare + real(1.0 / 12.0) * heightSquare;
        const real IxxAndzz = factor1 * mass * (sum1 + sum2) + factor2 * mass * sum3;
        const real Iyy = factor1 * mass * sum1 + factor2 * mass * real(0.25) * radiusSquareDouble;
        //   return Vector3(IxxAndzz, Iyy, IxxAndzz);

        mat.data[0][0]= IxxAndzz;
        mat.data[1][1]= IxxAndzz;
        mat.data[2][2]= Iyy;

        /*
         *

        Vector3 halfExtents(radius, radius, radius);
        halfExtents.z += length/2.0;

        real lx = real(2.) * (halfExtents.x);
        real ly = real(2.) * (halfExtents.y);
        real lz = real(2.) * (halfExtents.z);
        const real x2 = lx * lx;
        const real y2 = ly * ly;
        const real z2 = lz * lz;
        const real scaledmass = mass * real(.08333333);


        mat.data[0][0]= scaledmass * (y2 + z2);
        mat.data[1][1]= scaledmass * (x2 + z2);
        mat.data[2][2]= scaledmass * (x2 + y2);
         */

        return mat;
    }

    Vector3 getBase() const {
        return transform->unTransformPoint(-Vector3{0,0,(length/2.0)});
       }

    Vector3 getTip() const {
        return transform->unTransformPoint(Vector3{0,0,(length/2.0)});
    }


    bool collide(const SphereCollider &collider, CollisionData &data) const override {
        return false;
    }



       bool collide(const BoxCollider &collider, CollisionData &data) const override{
           return false;
       }


      // Vector3 clamp(Vector3 v, real min, real max){
      //     return {std::clamp(v.x,min, max),std::clamp(v.y,min, max),std::clamp(v.z,min, max)}; //todo make sure its component wise and not length
    //   }

    // Computes closest points C1 and C2 of S1(s)=P1+s*(Q1-P1) and
// S2(t)=P2+t*(Q2-P2), returning s and t. Function result is squared
// distance between between S1(s) and S2(t)
    real ClosestPtSegmentSegment(Vector3 p1, Vector3 q1, Vector3 p2, Vector3 q2,
                                  real &s, real &t, Vector3 &c1, Vector3 &c2) const
    {
        Vector3 d1 = q1 - p1; // Direction vector of segment S1
        Vector3 d2 = q2 - p2; // Direction vector of segment S2
        Vector3 r = p1 - p2;
        real a = d1.dot( d1); // Squared length of segment S1, always nonnegative
        real e = d2.dot( d2); // Squared length of segment S2, always nonnegative
        real f = d2.dot( r);

        const real EPSILON =0.00001;
        // Check if either or both segments degenerate into Vector3s
        if (a <= EPSILON && e <= EPSILON) {
            // Both segments degenerate into Vector3s
            s = t = 0.0f;
            c1 = p1;
            c2 = p2;
            return (c1 - c2).dot( c1 - c2);
        }
        if (a <= EPSILON) {
            // First segment degenerates into a Vector3
            s = 0.0f;
            t = f / e; // s = 0 => t = (b*s + f) / e = f / e
            t = std::clamp(t, 0.0, 1.0);
        } else {
            real c = d1.dot( r);
            if (e <= EPSILON) {
                // Second segment degenerates into a point
                t = 0.0f;
                s = std::clamp(-c / a, 0.0, 1.0); // t = 0 => s = (b*t - c) / a = -c / a
            } else {
                // The general nondegenerate case starts here
                real b = d1.dot( d2);
                real denom = a*e-b*b; // Always nonnegative
                // If segments not parallel, compute closest point on L1 to L2 and
                // clamp to segment S1. Else pick arbitrary s (here 0)
                if (denom != 0.0f) {
                    s = std::clamp((b*f - c*e) / denom, 0.0, 1.0);
                } else s = 0.0f;
                // Compute point on L2 closest to S1(s) using
                // t = Dot((P1 + D1*s) - P2,D2) / Dot(D2,D2) = (b*s + f) / e
                t = (b*s + f) / e;
                // If t in [0,1] done. Else clamp t, recompute s for the new value
                // of t using s = Dot((P2 + D2*t) - P1,D1) / Dot(D1,D1)= (t*b - c) / a
                // and clamp s to [0, 1]
                if (t < 0.0f) {
                    t = 0.0f;
                    s = std::clamp(-c / a, 0.0, 1.0);
                } else if (t > 1.0f) {
                    t = 1.0f;
                    s = std::clamp((b - c) / a, 0.0, 1.0);
                }
            }
        }
        c1 = p1 + d1 * s;
        c2 = p2 + d2 * t;
        return (c1 - c2).dot( c1 - c2);
    }



    bool collide(const CapsuleCollider &collider, CollisionData &data) const override {


        // Compute (squared) distance between the inner structures of the capsules
        real s, t;
        Vector3 c1, c2;
        real dist2 = ClosestPtSegmentSegment(getTip(), getBase(),
                                              collider.getTip(),   collider.getBase(), s, t, c1, c2);

//todo issues when colliders are parallel
        Vector3 penetration_normal = c1 - c2;//B -> A
        real len = penetration_normal.length();
        penetration_normal /= len;  // normalize
        real penetration_depth = radius + collider.radius - len;

        bool intersects = penetration_depth > 0;

        data.normal = penetration_normal;
        data.depth = penetration_depth;



        //todo switching this causes havok
        data.r2 = c1 + radius * -penetration_normal - transform->getPosition() ;//todo should it be updated here traqnform
        data.r1 = c2 + collider.radius * penetration_normal - collider.transform->getPosition();
//todo doc the a,b swap madness r1 r2
        if(intersects){
        //    std::cout << data.r1 << "\n";
            //   std::cout << penetration_depth << "\n";
        }

        return intersects;
    }


};

} // Doge
