//
// Created by Philip on 1/9/2023.
//

#pragma once

#include "../Physical.hpp"

namespace Doge {

    /**
     * An object that can be used in the XPBD system
     */
    class Constrainable : public Physical{
    private:
        int last_step_idx_before = -1;//flag to only before update once
        int last_step_idx_after = -1;//flag to only after update once
    public:

        //todo document
        Constrainable(real mass) : Physical(mass){}

        /**
         * Should be called by constraints using this object during it's beforeSolve()
         * @param sub_step_delta Delta time divided by # of sub steps
         * @param step_idx A number that is different from the last step, to make sure the object only updates once per step
        */
        void beforeSolve(const real& sub_step_delta, int step_idx) {
            if(last_step_idx_before != step_idx){ //Is new step, update
                beforeSolveIntegrate(sub_step_delta); //call the update
                last_step_idx_before = step_idx; //only update once
            }
        };

        /**
           * Should be called by constraints using this object during it's aferSolve()
           * @param sub_step_delta Delta time divided by # of sub steps
           * @param step_idx A number that is different from the last step, to make sure the object only updates once per step
          */
        void afterSolve(const real& sub_step_delta, int step_idx) {
            if(last_step_idx_after != step_idx){ //Is new step, update
                afterSolveIntegrate(sub_step_delta); //call the update
                last_step_idx_after = step_idx; //only update once
            }
        };


    protected:
        /**
         * What to perform before solving constraints in a sub step
         * @param sub_step_delta Delta time divided by # of sub steps
         */
        virtual void beforeSolveIntegrate(const real& sub_step_delta) = 0;

        //Constrains are applied externally

        /**
        * What to perform after solving constraints in a sub step
        * @param sub_step_delta Delta time divided by # of sub steps
        */
        virtual void afterSolveIntegrate(const real& sub_step_delta) = 0;
    };

} // Doge
