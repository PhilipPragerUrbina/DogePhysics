//
// Created by Philip on 1/9/2023.
//

#pragma once


#include "Collider.hpp"

namespace Doge {

    /**
     * Basic Bounding Box collision
     */
class BoxCollider : public Collider{
    private:
    Vector3 dimensions;
    BoundingSphere bounding;
    Transformable* transform;

    public:

    BoxCollider(Vector3 dimensions) : dimensions(dimensions) , bounding(0,0){
        bounding.radius = fmax(fmax(dimensions.x,dimensions.y), dimensions.z);
        //todo max better. Currently too large.
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
        mat.data[0][0]= (1.0/12.0)*mass * ((dimensions.y*dimensions.y)+(dimensions.z*dimensions.z));
        mat.data[1][1]= (1.0/12.0)*mass * ((dimensions.x*dimensions.x)+(dimensions.z*dimensions.z));
        mat.data[2][2]= (1.0/12.0)*mass * ((dimensions.x*dimensions.x)+(dimensions.y*dimensions.y));
        return mat;
    }

    bool inBox(const Vector3& point) const{
        Vector3 local_point = transform->transformPoint(point);
        Vector3 max = (dimensions/2.0);
        Vector3 min = (-dimensions/2.0);
        return local_point.x < max.x && local_point.y < max.y && local_point.z < max.z &&
        local_point.x > min.x && local_point.y > min.y && local_point.z > min.z;
       }



    Vector3 getClosestPoint(const Vector3& point) const {
           Vector3 local_point = transform->transformPoint(point);
           Vector3 closest_local_point = (dimensions/2.0).min( local_point); //Check max bound
           closest_local_point = (-dimensions/2.0).max(local_point);
        return transform->unTransformPoint(closest_local_point);
       }

    bool collide(const SphereCollider &collider, CollisionData &data) const override {
        return false;
    }

    bool collide(const BoxCollider &collider, CollisionData &data) const override {
        return false;
        Vector3 closest_a = getClosestPoint(collider.transform->getPosition());
        Vector3 closest_b = collider.getClosestPoint(transform->getPosition());
        if(!inBox(closest_b) && !inBox(closest_a) ){
            return false;
        }

        data.normal = -(closest_a - closest_b).normalized();
        data.depth = closest_a.distance(closest_b);

      //  data.position = closest_a;


        return true;
    }


};

} // Doge
