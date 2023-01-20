//
// Created by Philip on 1/9/2023.
//

#pragma once

#include "../../Collideable.hpp"
#include "../../Group.hpp"
#include "../Colliders/Collider.hpp"

namespace Doge {

    class CollisionLayer : public Group<Collideable>{
    public:
        /**
         * Run a full collision check and return list of collisions
         * @return List of collision data
         */
        std::vector<CollisionData> fullCheck(){
            findPotentialCollisions();
            return checkCollisions();
        }

        /**
         * Only find coarse potential collisions, not do actual check.
         */
        virtual void findPotentialCollisions() = 0;

        /**
         * Do actual collision check
         * Call after findPotentialCollisions() unless you want to check same pairs
         * @return List of collision data
         */
        virtual std::vector<CollisionData> checkCollisions() = 0;
        //todo doc
        //todo isStatic in collidable
        virtual std::vector<std::shared_ptr<Collideable>> * getContents() = 0;

    };


} // Doge
