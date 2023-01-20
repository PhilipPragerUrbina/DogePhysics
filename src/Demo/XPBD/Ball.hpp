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

class Ball : public Doge::GameObject{
private:
    std::shared_ptr<Doge::RigidBody> particle;
    Doge::SimpleDrag drag{0.55};
public:
    Ball(Doge::real mass, Doge::Vector3 position){
        particle = std::make_shared<Doge::RigidBody> (mass, new Doge::SphereCollider(1) );
        particle->setPosition(position);
       //particle->applyForce({0,-1,0});
    }

    std::shared_ptr<Doge::RigidBody> getParticle(){
        return particle;
    }


protected:


    void render(Doge::Renderer *renderer) override {
        renderer->drawSphere();

    }

    void update(Doge::real delta_time) override {


     //   drag.apply(particle.get());
        position = particle->getPosition();
        rotation = particle->getRotation();


    }

};

