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
            //check collide and add

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
            //loop thorugh potential
            return std::vector<CollisionData>();
        }

    };

} // Doge
