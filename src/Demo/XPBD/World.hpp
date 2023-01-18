//
// Created by Philip on 1/10/2023.
//

#pragma once


#include "../../DogeEngine/Scene/GameObject.hpp"
#include "../../DogePhysics/Constraints/ConstraintManager.hpp"
#include "Joint.hpp"

class World : public Doge::GameObject{
public:
    Doge::ConstraintManager manager{20};

    void addJoint(Joint* add){
        manager.add(add->getJoint());
        addChild(add);
    }
    void addBall(Ball* ball){
        addChild(ball);
    }

protected:



    void render(Doge::Renderer *renderer) override {

    }

    void update(Doge::real delta_time) override {
        manager.step(delta_time);
    }

};
