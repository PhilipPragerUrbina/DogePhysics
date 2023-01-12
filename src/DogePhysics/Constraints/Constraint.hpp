//
// Created by Philip on 1/9/2023.
//

#pragma once

#include "../../Utils/real.hpp"

namespace Doge {

    /**
     * XPBD constraint
     * Is put in a constraint manager
     */
    class Constraint {
    public:

        /**
         * What to perform before sub steps loop
         * Called only once per full simulation step
         */
        virtual void init() = 0;

        /**
         * What to perform before solving constraints in a sub step
         * Usually this means updating the constraint's objects by calling their beforeSolve()
         * @param sub_step_delta Delta time divided by # of sub steps
         *@param step_idx Pass down to objects that you are updating, so that they only update once per sub step
         */
        virtual void beforeSolve(const real& sub_step_delta, int sub_step_idx) = 0;

        /**
         * Solve constraint and update object positions
         * @param sub_step_delta Delta time divided by # of sub steps(Used for compliance in most cases)
         */
        virtual void solve(const real &sub_step_delta) = 0;


        /**
          * What to perform after solving constraints in a sub step
          * Usually this means updating the constraint's objects by calling their afterSolve()
          * @param sub_step_delta Delta time divided by # of sub steps
          * @param step_idx Pass down to objects that you are updating, so that they only update once per sub step
          */
        virtual void afterSolve(const real& sub_step_delta, int sub_step_idx) = 0;


    };

} // Doge
