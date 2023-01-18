//
// Created by Philip on 1/10/2023.
//

#pragma once


#include <memory>

#include "../../DogeEngine/Scene/GameObject.hpp"
#include "../../DogePhysics/Objects/XPBD/ParticleSystems/Particles/ConstrainableParticle.hpp"
#include "../../DogePhysics/ForceCalculators/SimpleDrag.hpp"
#include "../../DogePhysics/Objects/XPBD/RigidBody.hpp"

Doge::Matrix3 getCuboidTensor(Doge::real mass, Doge::Vector3 dim){
    Doge::Matrix3 mat{};
    mat.data[0][0]= (1.0/12.0)*mass * ((dim.y*dim.y)+(dim.z*dim.z));
    mat.data[1][1]= (1.0/12.0)*mass * ((dim.x*dim.x)+(dim.z*dim.z));
    mat.data[2][2]= (1.0/12.0)*mass * ((dim.x*dim.x)+(dim.y*dim.y));
    return mat;
}

class Ball : public Doge::GameObject{
private:
    std::shared_ptr<Doge::RigidBody> particle;
    Doge::SimpleDrag drag{0.55};
public:
    Ball(Doge::real mass, Doge::Vector3 position){
        particle = std::make_shared<Doge::RigidBody> (mass, getCuboidTensor(mass,{1,1,1}));
        particle->setPosition(position);
       //particle->applyForce({0,-40,0});
    }

    std::shared_ptr<Doge::RigidBody> getParticle(){
        return particle;
    }


protected:


    void render(Doge::Renderer *renderer) override {
        renderer->drawCube();

    }

    void update(Doge::real delta_time) override {


     //   drag.apply(particle.get());
        position = particle->getPosition();
        rotation = particle->getRotation();

    }

};

