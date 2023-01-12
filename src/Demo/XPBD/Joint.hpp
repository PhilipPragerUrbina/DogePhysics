//
// Created by Philip on 1/11/2023.
//

#pragma once

#include "../../DogeEngine/Scene/GameObject.hpp"
#include "../../DogePhysics/Constraints/ConstraintManager.hpp"
#include "../../DogePhysics/Constraints/Fixed/DistanceConstraint.hpp"
#include "Ball.hpp"

class Joint : public Doge::GameObject{
private:
    std::shared_ptr<Doge::DistanceConstraint> constraint;

public:
    Joint(Ball* a, Ball* b, Doge::real length){
        constraint = std::make_shared<Doge::DistanceConstraint>(a->getParticle(),b->getParticle(),length);
    }
    std::shared_ptr<Doge::DistanceConstraint> getJoint(){
        return constraint;
    }


protected:

    void render(Doge::Renderer *renderer) override {

    }

    void update(Doge::real delta_time) override {


    }


};
