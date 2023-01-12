//
// Created by Philip on 1/10/2023.
//

#pragma once


#include <memory>

#include "../../DogeEngine/Scene/GameObject.hpp"
#include "../../DogePhysics/Objects/XPBD/ParticleSystems/Particles/ConstrainableParticle.hpp"
#include "../../DogePhysics/ForceCalculators/SimpleDrag.hpp"


class Ball : public Doge::GameObject{
private:
    std::shared_ptr<Doge::ConstrainableParticle> particle;
    Doge::SimpleDrag drag{0.55};
public:
    Ball(Doge::real mass, Doge::Vector3 position){
        particle = std::make_shared<Doge::ConstrainableParticle> (mass);
        particle->setPosition(position);
        particle->applyForce({0,-40,0});

    }

    std::shared_ptr<Doge::ConstrainableParticle> getParticle(){
        return particle;
    }


protected:


    void render(Doge::Renderer *renderer) override {
        renderer->drawSphere();

    }

    void update(Doge::real delta_time) override {



     //   drag.apply(particle.get());
        position = particle->getPosition();

    }

};
