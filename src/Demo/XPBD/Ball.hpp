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
#include "../../DogePhysics/Collisions/Colliders/CapsuleCollider.hpp"
class Ball : public Doge::GameObject{
private:
    std::shared_ptr<Doge::RigidBody> particle;
    Doge::SimpleDrag drag{0.55};
    bool action;
    int amount = 0;
    double size;
    double ss;
public:
    Ball(Doge::real mass, Doge::Vector3 position,double s, bool move = false){
        ss=10;
        size = s;
        action = move;
        particle = std::make_shared<Doge::RigidBody> (mass, new Doge::CapsuleCollider(size*ss, size) );//todo box collider
        particle->setPosition(position);
       //particle->applyForce({0,-1,0});
    }

    std::shared_ptr<Doge::RigidBody> getParticle(){
        return particle;
    }


protected:


    void render(Doge::Renderer *renderer) override {
        //Cat
/*
        renderer->pushMatrix();
        renderer->translate({0,-0.4,0});
        renderer->rotate(90,{0,1,0});
        renderer->scale({0.1,0.1,0.1});
        renderer->drawMesh(4);
        renderer->popMatrix();
*/
       //  Capsule

        renderer->pushMatrix();
        renderer->translate({0,0,size* ss * 0.5});
        renderer->scale(size);
        renderer->drawSphere();
        renderer->scale(1.0/size);
        renderer->translate({0,0,-size * ss });
        renderer->scale(size);
        renderer->drawSphere();
        renderer->popMatrix();
        renderer->rotate(90,{1,0,0});
        renderer->scale({size,size*ss,size});
        renderer->drawCylinder();



    }

    void update(Doge::real delta_time) override {


     //   drag.apply(particle.get());
        position = particle->getPosition();
        rotation = particle->getRotation();


        if(action){
            amount++;
            if(amount > 500){
                particle->setPosition(particle->getPosition() - Doge::Vector3{0.2,0,0});
                action = false;
            }
        }


    }

};

