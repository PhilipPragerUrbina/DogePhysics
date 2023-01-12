//
// Created by Philip on 1/9/2023.
//

#pragma once

#include "../Updateable.hpp"
#include "../Group.hpp"
#include "Constraint.hpp"

namespace Doge {

    /**
     * Manage and update XPBD constrains
     */
class ConstraintManager : public Updateable , public Group<Constraint>{
    private:
        int sub_step_idx = 0; //just a number that is different every sub step
        const int num_sub_steps;
    public:

        /**
         * Create a new manager to manage XPBD constraints and their objects
         * @param num_sub_steps # of sub steps every simulation step
         */
        explicit ConstraintManager(const int num_sub_steps) : num_sub_steps(num_sub_steps){}


        /**
         * Step the XPBD simulation
         * @param delta_time
         */
        void step(real delta_time) override{



            real sub_step_delta = delta_time / (real)num_sub_steps; //Calculate "h" the delta time per sub step
            for (unsigned int i = 0; i < getSize(); ++i) {
                //Before running sub steps, do anything that needs to be done only once every full step
                get(i)->init();
            }

            //Run sub steps
            for (int i = 0; i < num_sub_steps; ++i) {
                //Let me explain this
                //We need a number that is different from the number last sub_step
                //We increment it to achieve this, and then modulo it to an arbitrary number(200) to stop eventual overflow since counting up forever is not necessary
                sub_step_idx = (sub_step_idx + 1) % 200;

                //Loop through the constraints 3 times per sub step(order matters)
                for (unsigned int j = 0; j < getSize(); ++j) {
                    //Update the objects in the constraints
                    get(j)->beforeSolve(sub_step_delta, sub_step_idx);
                }
                for (unsigned int j = 0; j < getSize(); ++j) {
                    //Solve constraints
                    get(j)->solve(sub_step_delta);
                }
                for (unsigned int j = 0; j < getSize(); ++j) {
                    //Update the objects in the constraints based on solve
                    get(j)->afterSolve(sub_step_delta, sub_step_idx);
                }
            }


        }


    };

} // Doge
