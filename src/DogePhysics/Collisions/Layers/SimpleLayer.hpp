//
// Created by Philip on 1/17/2023.
//

#pragma once

#include "CollisionLayer.hpp"

namespace Doge {

    /**
     * Simple slow collision layer
     */
    class SimpleLayer : public CollisionLayer{
    private:
        std::vector<PotentialCollision> potential_collisions;

        //check to others and add to potential
        void coarceCollide(Collideable* body1){
            for (int i = 0; i < getSize(); ++i) {
                Collideable* body2 = get(i);
                if(body1 == body2){
                    continue;
                }
            if(body1->getCollider()->coarseCollision(body2->getCollider())){
                potential_collisions.emplace_back(body1,body2);
            }

            }
        }
    public:
        void findPotentialCollisions() override {
            potential_collisions.clear();
            for (int i = 0; i < getSize(); ++i) {
                Collideable* body1 = get(i);
                coarceCollide(body1);
            }
        }

        std::vector<CollisionData> checkCollisions() override {
            std::vector<CollisionData> out;
            for (PotentialCollision potential_collision : potential_collisions) {
                CollisionData data;
                if(potential_collision.a->getCollider()->collide(potential_collision.b->getCollider(),data)){
                    data.a = potential_collision.a; //todo make sure order is correct
                    data.b = potential_collision.b;
                    out.push_back(data);
                }
            }

            return out;
        }

        std::vector<std::shared_ptr<Collideable>> * getContents() override {
            return getObjects();
        }

    };

} // Doge
