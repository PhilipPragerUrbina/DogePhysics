//
// Created by Philip on 12/27/2022.
//

#pragma once

#include "../../../Utils/real.hpp"
#include "../../../Utils/Vector3.hpp"

namespace Doge {

    /**
     * A single point in space with mass
     */
    class Particle {
    private:
        real inverse_mass; //1/mass
        real damping; //damping applied to linear motion

        Vector3 position;
        Vector3 velocity; //change in position over time
        Vector3 acceleration; //change in velocity over time (m/s^2)
        Vector3 net_force;
    public:
        /**
         * Create a new particle
         * @param start_position Start position (m)
         * @param start_velocity Starting velocity (m/s)
         * @param mass Mass of particle
         * @param damping How much velocity is left each integration
         */
        Particle(const Vector3& start_position, const Vector3& start_velocity = {0,0,0}, real mass = 1, real damping = 0.95) : position(start_position), velocity(start_velocity), damping(damping){
            setMass(mass);
        }

        /**
         * Set the mass of the particle
         * @param mass
         */
        void setMass(real mass){
            inverse_mass = 1.0f/mass;
        }

        /**
         * Integrate or simulate the particle using Newton-Euler method
         * @param delta_time How much time forward to simulate
         */
        virtual void step(const real delta_time){
            position += velocity * delta_time; //update linear position
            //Use the constant acceleration + the acceleration due to the net force
            velocity += (acceleration + (net_force*inverse_mass)) * delta_time; //update velocity
            velocity *= pow(damping ,delta_time);  //damping(time scaled).
            resetNetForce();
        }

        /**
         * Return true if alive(should not be removed)
         * @return Status
         */
        virtual bool alive(){
            return true;
        }

        /**
         * Reset the net force that was calculated for this step
         */
        inline void resetNetForce(){
            net_force = 0;
        }

        /**
         * Apply a force to the object for the duration of this step only.
         * @param force Force in newtons
         */
        void applyForce(const Vector3& force){
            net_force += force;
        }

        /**
         * Set the constant acceleration of the particle
         */
        void setAcceleration(const Vector3& new_accel){
            acceleration = new_accel;
        }


        /**
         * Get the position of the particle
         */
        Vector3 getPosition() const{
            return position;
        };

        /**
         * Get the Velocity of the particle
         */
        Vector3 getVelocity() const{
            return velocity;
        };
    };

} // Doge
