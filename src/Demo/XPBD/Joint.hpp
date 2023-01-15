//
// Created by Philip on 1/11/2023.
//

#pragma once

#include "../../DogeEngine/Scene/GameObject.hpp"
#include "../../DogePhysics/Constraints/ConstraintManager.hpp"
#include "../../DogePhysics/Constraints/Fixed/DistanceConstraint.hpp"
#include "Ball.hpp"
#include "../../DogePhysics/Constraints/Fixed/DistanceConstraintRigid.hpp"

class Joint : public Doge::GameObject{
private:
    std::shared_ptr<Doge::DistanceConstraintRigid> constraint;

public:
    Joint(Ball* a, Ball* b, Doge::real length, Doge::real inv_stiffness = 0){
        constraint = std::make_shared<Doge::DistanceConstraintRigid>(a->getParticle(),b->getParticle(),length,inv_stiffness);
    }
    std::shared_ptr<Doge::DistanceConstraintRigid> getJoint(){
        return constraint;
    }


protected:

    void render(Doge::Renderer *renderer) override {

    }

    void update(Doge::real delta_time) override {


    }


};
