#include <memory>

#include "../../DogeEngine/Scene/SceneGraph.hpp"
#include "World.hpp"
#include "Ball.hpp"
#include "../../DogePhysics/Constraints/Fixed/DistanceConstraint.hpp"

//
// Created by Philip on 1/10/2023.
//
void createSceneXPBD(Doge::SceneGraph* scene){
World* world = new World;
scene->addObject(world);

    Ball* last_ball = new Ball(100000,{0,0,0});

    Ball* first_ball = last_ball;
    world->addBall(last_ball);
    for (int i = 1; i < 100; ++i) {
        Ball* new_ball = new Ball(1, {(Doge::real)i*3,0,0} );
        Joint* new_joint = new Joint(last_ball,new_ball,3);
        world->addBall(new_ball);
        world->addJoint(new_joint);
        last_ball = new_ball;
    }
    //last_ball->getParticle()->setMass(1000); //heavy end

    //loop
   // world->addJoint(new Joint(last_ball,first_ball,3));


//todo drawline



}