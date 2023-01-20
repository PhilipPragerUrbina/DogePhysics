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

Ball* ball = new  Ball(100,{0,0,0});
ball->getParticle()->setVelocity({1,10,5});
//Newton cradle
//ball->getParticle()->setVelocity({0,10,0});
world->addBall(ball);

//todo newtons cradle
//todo why so bouncy, should be inelastic


Ball* ball2 = new  Ball(100,{0,3,0});
world->addBall(ball2);
    Ball* ball3 = new  Ball(100,{0,5,0});
    world->addBall(ball3);

    Ball* ball4 = new  Ball(100,{0,7,0});
    world->addBall(ball4);

/**
    Ball* last_ball = new Ball(10,{0,0,0});

    Ball* first_ball = last_ball;
    world->addBall(last_ball);
    for (int i = 1; i < 2; ++i) {
        Ball* new_ball = new Ball(10, {(Doge::real)i*5,0,0} );
        Joint* new_joint = new Joint(last_ball,new_ball,5,0); //todo something is propagating nans
        world->addBall(new_ball);
        world->addJoint(new_joint);
        last_ball = new_ball;
    }**/

    //last_ball->getParticle()->setMass(1000); //heavy end

    //loop
   // world->addJoint(new Joint(last_ball,first_ball,3));

/*
   const int w = 20;
   Ball* cloth[w][w];
    for (int x = 0; x < w; ++x) {
        for (int y = 0; y < w; ++y) {
            cloth[x][y] = new Ball(1, {(Doge::real)x*4, (Doge::real)y*4,0});
            world->addBall(cloth[x][y]);
        }
    }
    for (int x = 0; x < w; ++x) {
        for (int y = 0; y < w; ++y) {
            if(x < w-1){
                world->addJoint(new Joint(cloth[x][y],cloth[x+1][y], 4,0.0005));
            }
            if(y < w-1){
                world->addJoint(new Joint(cloth[x][y],cloth[x][y+1], 4,0.0005));
            }
        }
    }
    for (int x = 0; x < w; ++x) {
        cloth[x][0]->getParticle()->setMass(100000);

    }*/






//todo drawline



}