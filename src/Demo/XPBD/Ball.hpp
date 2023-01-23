//
// Created by Philip on 1/10/2023.
//

#pragma once


#include <memory>

#include "../../DogeEngine/Scene/GameObject.hpp"
#include "../../DogePhysics/Objects/XPBD/ParticleSystems/Particles/ConstrainableParticle.hpp"
#include "../../DogePhysics/ForceCalculators/SimpleDrag.hpp"
#include "../../DogePhysics/Objects/XPBD/RigidBody.hpp"
#include "../../DogePhysics/Collisions/Colliders/SphereCollider.hpp"
#include "../../DogePhysics/Collisions/Colliders/BoxCollider.hpp"
class Ball : public Doge::GameObject{
private:
    std::shared_ptr<Doge::RigidBody> particle;
    Doge::SimpleDrag drag{0.55};
    bool action;
    int amount = 0;
    double size;
public:
    Ball(Doge::real mass, Doge::Vector3 position,double s, bool move = false){
        size = s;
        action = move;
        particle = std::make_shared<Doge::RigidBody> (mass, new Doge::BoxCollider(size) );//todo box collider
        particle->setPosition(position);
       //particle->applyForce({0,-1,0});
    }

    std::shared_ptr<Doge::RigidBody> getParticle(){
        return particle;
    }


protected:


    void render(Doge::Renderer *renderer) override {
        renderer->scale(size);
        renderer->drawSphere();
        renderer->drawCube();

    }

    void update(Doge::real delta_time) override {


     //   drag.apply(particle.get());
        position = particle->getPosition();
        rotation = particle->getRotation();


        if(action){
            amount++;
            if(amount > 1){
                particle->setPosition(particle->getPosition() - Doge::Vector3{0.1,0,0});
                action = false;
            }
        }


    }

};

