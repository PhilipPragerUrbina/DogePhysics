//
// Created by Philip on 12/28/2022.
//

#pragma once

#include "Particle.hpp"

namespace Doge {

    /**
     * A particle that keeps track of it's lifetime and kills itself when the lifetime is over
     */
    class LifetimeParticle : public Particle{
    private:
        real lifetime = 0;
        const real max_lifetime;
    public:

        /**
         * Same as normal particle
         * @param max_lifetime How long the particle should stay alive
         */
        LifetimeParticle(const real max_lifetime , const Vector3& start_position, const Vector3& start_velocity = {0,0,0}, real mass = 1, real damping = 0.95) : Particle(start_position,start_velocity,
                                                                                                                                                mass, damping) , max_lifetime(max_lifetime) {}

        /**
         * Same thing as normal particle integration but counts lifetime
         */
        void step(const real delta_time) override {
            Particle::step(delta_time);
            lifetime += delta_time;
        }

        /**
         * Check if the particle is within its maximum lifespan
         */
        bool alive() override {
            return lifetime < max_lifetime;
        }

        /**
         * Get how long the particle has been simulated in seconds
         */
        real getLifeTime() const {
            return lifetime;
        }

        /**
         * Set the particles lifetime(how long it has been alive)
         */
        void setLifeTime(real new_lifetime){
            lifetime = new_lifetime;
        }

        /**
         * Get the maximum lifetime set for this particle
         */
        real getMaxLifeTime(){
            return max_lifetime;
        }


    };

} // Doge
