//
// Created by Philip on 1/9/2023.
//

#pragma once

#include "../Transformable.hpp"
#include "cassert"
namespace Doge {

    /**
     * Has physical properties
     * Can sustain forces
     */
    class Physical : public Transformable{
    private:
        real inverse_mass; //1/mass
    protected:
        Vector3 velocity; //all physical objects have a velocity
        Vector3 net_force; //accumulative external force
    public:

        /**
         * Create a physical object that forces can be applied to
         * @param start_mass Mass in kilograms
         */
        Physical(real start_mass) {
            setMass(start_mass);
        }

        /**
         * Get the inverse mass
         */
        real getInverseMass() const {
            return inverse_mass;
        }

        /**
         * Add force to the net force that will be applied until force is reset(Usually reset every simulation step)
         * @param force Force to apply in newtons
         */
        void applyForce(const Vector3& force){
            net_force += force;
        }

        /**
         * Reset the net force.
         */
        void resetNetForce(){
            net_force = 0;
        }

        /**
         * Set the mass of the objects in kilograms
         */
        void setMass(real new_mass){
            assert(new_mass > 0.0f);
            inverse_mass = 1.0f/new_mass;
        }

        /**
         * Set the inverse mass directly
         * @param new_inverse_mass Set to 0 for infinite mass
         */
        void setInverseMass(real new_inverse_mass){
            inverse_mass = new_inverse_mass;
        }

        /**
         * Get the velocity in m/s
         */
        Vector3 getVelocity() const {
            return velocity;
        }

    };

} // Doge
