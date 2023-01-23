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


    Ball* ball = new  Ball(1000000,{0,-3,0}, 5,true);
    world->addBall(ball);

    //todo get proper box collisions
    //todo make sure rotations are working
    //todo clean up
    //todo UX
    //https://matthias-research.github.io/pages/publications/PBDBodies.pdf

    //todo upper balls not moving? seem to have more mass? I think its float precision. Changes too miniscule to allow the larger numbers to build up speed? Only happens with float?
    //todo two falling balls get stuck together in collision.
    //can handle a thousand
    for (int i = 0; i < 20; ++i) {
        Ball* ball2 = new  Ball(1,{0,(Doge::real)i*3.0f*((i+2)/10.0),0},(double)(i+2)/10);
        ball2->getParticle()->setAngularVelocity({0,0,0.2});
        //ball2->getParticle()->applyForce({0,-50,0});

        world->addBall(ball2);
    }


    //todo review the r1 and r2
    //todo Try angular velocity
    //todo do box collision detection tutorial



/**
Ball* ball = new  Ball(100,{0,-2,0});
ball->getParticle()->setVelocity({1,10,2});
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
    world->addBall(ball4);**/

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