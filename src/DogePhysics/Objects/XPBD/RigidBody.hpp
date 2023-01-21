//
// Created by Philip on 1/9/2023.
//

#pragma once

#include "Constrainable.hpp"
#include "../../Collideable.hpp"

namespace Doge {
    //todo world vs object space

    /**
     * A physical object with rotation
     */
    class RigidBody : public Constrainable, public Collideable{
    private:
        Quaternion prev_rotation; //Last rotation value
        Vector3 prev_position; //Last position value
        Vector3 angular_velocity; //Change in rotation over time
        Matrix3 inverse_intertia; //Inverse intertia tensor. Equivalent to inverse mass for rotation.
    public:

        /**
         * Create a rigid body
         * @param mass Mass todo units
         * @param intertia_tensor Intertia
         */
        RigidBody(real mass, Collider* rigid_collider) : Constrainable(mass) , Collideable(rigid_collider){
            setIntertiaTensor(rigid_collider->createInertiaTensor(mass));
        }

        /**
         * Set the Intertia tensor in body space
         * @param new_tensor Must not be degenerate
         */
        void setIntertiaTensor(const Matrix3& new_tensor){
            inverse_intertia = new_tensor.inverse();//todo convert to world space
        }

        /**
         * Get Inverse inertia tensor for constraint calculations
         */
        Matrix3 getInverseIntertia() const {
            return inverse_intertia;
        }

        //todo clean up and doc
        void setVelocity(Vector3 v){
            velocity = v;
        }

        //todo clear accumulators
        //todo apply rotational forces

    protected:
        //todo cite paper
        void beforeSolveIntegrate(const real &sub_step_delta) override {
            //Corresponds to first "for n particles and bodies" loop
            prev_position = position; //Store last position
            prev_rotation = rotation; //Store last rotation


        velocity += sub_step_delta * net_force * getInverseMass(); //update velocity with external forces
            //todo add external forces to angular velocity using inertia tensor

            position += sub_step_delta * velocity; //update position
            rotation.addVector(angular_velocity,sub_step_delta); //Update rotation(Does automatic conversion)
            rotation.normalize();
            //todo nicer add vector
        }

        void afterSolveIntegrate(const real &sub_step_delta) override {

            //Corresponds to second "for n particles and bodies" loop

            velocity = (position - prev_position)/sub_step_delta; //Update velocity after constrains

            //Get rotation delta
            Quaternion rotation_delta = rotation;
            rotation_delta *= prev_rotation.inverse();

            angular_velocity = 2.0 * Vector3{rotation_delta.i, rotation_delta.j, rotation_delta.k} / sub_step_delta; //Update angular velocity
            //Set direction of velocity
            angular_velocity = rotation_delta.r >= 0 ? angular_velocity : -angular_velocity;


                    //todo variable names to equation names

        }




    };

} // Doge
