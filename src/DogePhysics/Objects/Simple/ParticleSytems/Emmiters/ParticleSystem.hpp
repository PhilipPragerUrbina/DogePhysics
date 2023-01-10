//
// Created by Philip on 12/29/2022.
//

#pragma once

#include <type_traits>
#include <vector>
#include <functional>
#include "../particles/Particle.hpp"

namespace Doge {
    /**
     * Manages particles in the particle system
     */
    class ParticleSystem {
    private:
        std::vector<std::unique_ptr<Particle>> particle_buffer; //Keep track of the particles
        //Unique pointer to allow use of polymorphism

        int num_particles = 0; //Number of currently active particles

    public:
        /**
         * Create a new particle system
         * @param start_particles Expected number of particles. Used to pre-allocate space in the particle buffer. Not the maximum amount.
         */
        explicit ParticleSystem(const int start_particles = 100) : particle_buffer(start_particles){}

        /**
         * Add a particle to the particle system, to be simulated
         * The particle system will manage the memory lifetime of the particle using unique pointer
         * It will delete the particle once the particle no longer claims to be alive(), or once the particle system is destroyed
         * @param particle Pointer to a new allocated polymorphic particle to add to the simulation. Can and should be a child of the particle base class.
         * The derived particle you pass into here should have its behavior defined in the step() and  alive() methods.
         * @warning Do not create new particles in the step() method of the particle, use processParticles() instead
         */
        void addParticle(Particle* particle){
            num_particles++;
            //Find free position
            for (std::unique_ptr<Particle>& buffer_space : particle_buffer) {
                if(!buffer_space){ //free spot found. Null unique pointer is used as a flag for a free spot
                    buffer_space = std::unique_ptr<Particle>(particle); //Use unique pointer to manage memory
                    return;
                }
            }
            //free spot not found
            particle_buffer.push_back(std::unique_ptr<Particle>(particle));
        }

        /**
         * Step the particles and kill them if needed
         * @param delta_time Simulation delta time
         */
        virtual void step(real delta_time){
            for (std::unique_ptr<Particle>& buffer_space : particle_buffer) {
                if(buffer_space){ //particle exists
                    //This order is important, by doing the step at the end, we can also check if a particle is about do die in other places in the loop, such as updateParticles()
                    if(!buffer_space->alive()){ //check if alive
                        num_particles--;
                        buffer_space.reset(); //kill(release memory and set to null flag)
                    }else{
                        buffer_space->step(delta_time); //simulate
                    }

                }
            }
        }

        /**
         * Render each particle using a single method. Best for simple render cases.
         * @param render_method The method or lambda to use to render each active particle. Takes a parameter of a pointer to the particle being rendered(you can cast to any derived particle class of your choice).
         * For example, if you created your particle as a colored particle, you can cast it as a colored particle in the rendered method to get its color, rather than just getting the base particle information(careful if you have multiple particle types).
         * @warning Do not create new particles here, use processParticles()
         */
        void renderParticles(const std::function<void(Particle*)>& render_method){
            for (std::unique_ptr<Particle>& buffer_space : particle_buffer) {
                if(buffer_space){
                    render_method(buffer_space.get());
                }
            }
        }

        /**
         * This method should be used to get information or apply changes to particles to add extra behaviors.
         * Most behaviors can be programmed into the step() method of the particle, but any behavior that can't be added there should use this.
         * @important This method is the only way to spawn more particles based on other particles.
         * This can not be done in the step() or renderParticles() methods, since adding more particles would cause problems with iteration, but adding more particles is fine using this method.
         * @example Spawning additional particles, from the position of each particle for things like fireworks.
         * @details This method uses a fixed loop which has no problems with adding spawning more particles during iteration. Some new particles created during this method call will be processed in the same call if
         * they fill in free spots, but most new particles will not be processed until the method is called again.
         * @param render_method The only functional difference compared to the renderParticles method, is that this one also passes in a reference to the particle system as well, to allow particles to spawn more particles if they so please.
         * @usage Similar to renderParticles() method in terms of usage otherwise.
        */
        void processParticles(const std::function<void(Particle*, ParticleSystem*)>& render_method){
            int initial_size = particle_buffer.size(); //get a fixed size to avoid infinite loop if new particles are added during iteration
            for (int i = 0; i < initial_size; i++) { //Use a fixed loop
                std::unique_ptr<Particle>& buffer_space = particle_buffer[i]; //Get the particle
                if(buffer_space){
                    render_method(buffer_space.get(), this);
                }
            }
        }

        /**
         * Get the # of particles that are currently active
         */
        int getParticleCount() const{
            return num_particles;
        }

        //todo method for getting a particle buffer(positions, velocities, etc) or copying to one , for more optimized and complex rendering such as GL_POINTS.

    };

} // Doge
