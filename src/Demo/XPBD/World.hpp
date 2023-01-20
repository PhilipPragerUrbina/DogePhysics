//
// Created by Philip on 1/10/2023.
//

#pragma once


#include "../../DogeEngine/Scene/GameObject.hpp"
#include "../../DogePhysics/Constraints/ConstraintManager.hpp"
#include "../../DogePhysics/Collisions/Layers/CollisionLayer.hpp"
#include "Joint.hpp"
#include "../../DogePhysics/Collisions/Layers/SimpleLayer.hpp"
#include "../../DogePhysics/Constraints/Groups/CollisionSolver.hpp"

class World : public Doge::GameObject{
public:
    Doge::ConstraintManager manager{10};
    std::shared_ptr<Doge::CollisionLayer> layer;
    std::shared_ptr<Doge::CollisionSolver> solver;

    void addJoint(Joint* add){
        manager.add(add->getJoint());
        addChild(add);
    }
    void addBall(Ball* ball){
        layer->add(ball->getParticle());
        addChild(ball);
    }

    World(){
        layer = std::shared_ptr<Doge::CollisionLayer>(new Doge::SimpleLayer());
        solver = std::shared_ptr<Doge::CollisionSolver>(new Doge::CollisionSolver(layer,0.00001));
        manager.add(solver);
    }

protected:



    void render(Doge::Renderer *renderer) override {

    }

    void update(Doge::real delta_time) override {
        manager.step(delta_time);
    }

};
