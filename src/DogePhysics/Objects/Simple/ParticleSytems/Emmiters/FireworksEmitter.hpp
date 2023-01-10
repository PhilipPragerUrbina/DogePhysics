//
// Created by Philip on 12/27/2022.
//

#pragma once

#include <vector>
#include "../../Particles/LifetimeParticle.hpp"
#include "../../../../Utils/Random.hpp"
#include "../ParticleSystem.hpp"
#include <array>
namespace Doge {

    /**
     * Emit firework particles
     */
    class FireworksEmitter : public ParticleSystem{
    private:
        //settings
        int payloads, start_particles;
        Vector3 min_velocity, max_velocity;
        real max_lifetime, lifetime_variation, split_factor;
        real gravity, damping;

        /**
         * Estimate the final # of particles for this firework' simulation.
         * @param start Start amount of fireworks
         * @param iterations The # of times each firework will explode into more fireworks
         * @param factor How the fireworks  emitted will change every iteration
         * @return The # of active particles after 1 full emission and all payloads have been released.
         * May be off by a little, but close enough
         */
        static int estimateParticleCount(const int start, const int iterations, const real factor){
            real count = (real)start; //Start with the # of starting fireworks
            for(int i = 1; i < iterations+1; i++){ //For each iteration. Not including first one.
                real new_count = count * (start * pow(factor,i)); //Multiply the last iterations count by the number of new fireworks per firework.
                if(new_count < count){ //Get maximum number, exit early if regressing
                    break;
                }
                count = new_count;
            }
            //std::cout << "Predicted : " << (int)(count) << "\n\n";
            return (int)(count); //Get the final count.
        }

    public:

        /**
         * Create a firework emitter based on a bunch of settings
         * @param payloads # of times for particles to explode. How many iterations of fireworks. How "nested" the fireworks are.
         * @param start_particles # of fireworks for the initial launch
         * @param split_factor How to change the # of particles released after each nested explosion. 0.5 means each child firework will launch 0.5 times as many fireworks on explosion as its parent.
         * @param min_velocity Minimum random velocity to start with after being spawned
         * @param max_velocity Maximum random velocity to start with after being spawned
         * @param max_lifetime Maximum time for a firework to exist before de-spawning or exploding in seconds
         * @param lifetime_variation Maximum a mount of variation a firework can have in is lifespan in seconds.
         * @param gravity acceleration(Y)
         * @param damping How much velocity left over time.Usually low for fireworks.
         * @warning Allocates array for estimated final active particle count. Do not use settings that will create an unreasonable # of particles, since it will cause this to crash if a too large array is needed.
         */
        FireworksEmitter(int payloads = 3, int start_particles = 30, real split_factor = 0.4, const Vector3 &min_velocity = {-2}, const Vector3 &max_velocity = {2},
                         real max_lifetime = 3, real lifetime_variation = 1, real gravity = -2, real damping = 0.2) : payloads(payloads), start_particles(start_particles),
                                                     min_velocity(min_velocity), max_velocity(max_velocity),
                                                     max_lifetime(max_lifetime), lifetime_variation(lifetime_variation),
                                                     gravity(gravity), damping(damping), split_factor(split_factor),
                                                     ParticleSystem(estimateParticleCount(start_particles,payloads,split_factor)){} //init system with calculation of the maximum # of particles that will be created to improve performance.
    private:
        /**
         * Emit particles in random directions
         * @param amount How many to emit
         * @param position Where to start
         * @param start_velocity What velocity to start with
         * @param stage What iteration of payloads this particle is part of. (parent + 1).
         */
        void emit(const int amount, const Vector3& position, const Vector3& start_velocity, int stage){
            for (int i = 0; i < amount; ++i) {
                Firework* particle = new Firework(stage, Doge::Random::randomReal(max_lifetime-lifetime_variation,max_lifetime),position,start_velocity+Doge::Random::randomVector(min_velocity,max_velocity),damping);
                particle->setAcceleration({0,gravity,0});
                addParticle(particle);
            }
        }
    public:

        /**
         * Simple firework particle type
         */
        class Firework : public LifetimeParticle{
        private:
            int stage; //The stage the particle is in. How many times it has been exploded.
        public:
            Firework(int stage , const real max_lifetime , const Vector3& start_position, const Vector3& start_velocity , real damping) : LifetimeParticle(max_lifetime,start_position,start_velocity,1, damping), stage(stage) {} //mass is always 1
            int getStage() const{
                return stage; //todo render differently based on stage
            }
        };


        /**
         * Emit fireworks
         * @param position Where to emit
         */
        void launch(const Vector3& position){
            //todo store position as physics object
            emit(start_particles,position,{0}, 0);
        }


        /**
         * Simulate the fireworks
         * @param delta_time
         */
       void step(real delta_time) override {
           processParticles([this](Particle* particle, ParticleSystem* system){
               Firework* firework = (Firework*)particle;
               if(firework->getStage() < payloads && !firework->alive()  ){ //Dead and still has payload
                   //Calculate # of particles using exponential equation
                   //emit particles
                   emit((int)(start_particles * pow(split_factor, firework->getStage()+1)),firework->getPosition(),firework->getVelocity(),firework->getStage() + 1);
               }
           });
           ParticleSystem::step(delta_time);
       }

    };



} // Doge
