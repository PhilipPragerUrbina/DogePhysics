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




    for (int i = -4; i < 10; ++i) {
        Ball* ball = new  Ball(100000,{(Doge::real)i * 4.2,-3.1,0}, 2, false);
        world->addBall(ball);
    }


    int height = 40;
    double width = 1.1;
    double spacing = 3;

    for (int i = 0; i < height; i+=2) {
        Ball* ball2 = new  Ball(1,{-width, i * spacing ,0},1);
        ball2->getParticle()->applyForce({0,-9.8,0});
        world->addBall(ball2);
        Ball* ball3 = new  Ball(1,{width, i * spacing ,0},1);
        ball3->getParticle()->applyForce({0,-9.8,0});
        world->addBall(ball3);

    }


    for (int i = 1; i < height+1; i+=2) {
        Ball* ball2 = new  Ball(1,{0, i * spacing ,-width},1);
        Doge::Quaternion rot = ball2->getParticle()->getRotation();
        ball2->getParticle()->applyForce({0,-9.8,0});
        rot.addVector({0,M_PI/1.5,0});
        ball2->getParticle()->setRotation(rot);
        world->addBall(ball2);

        Ball* ball3 = new  Ball(1,{0, i * spacing ,width},1);
        ball3->getParticle()->applyForce({0,-9.8,0});
        ball3->getParticle()->setRotation(rot);
        world->addBall(ball3);

    }



    //todo clean up
    //todo UX
    //https://matthias-research.github.io/pages/publications/PBDBodies.pdf



    //can handle a thousand
    for (int i = 1; i < 0; ++i) {
        double size = (i + 5) /10.0;
        size = 1;
        Ball* ball2 = new  Ball(1,{0,(Doge::real)i*3.0f*size + 10  ,0},size);
        Doge::Quaternion rot = ball2->getParticle()->getRotation();
        rot.addVector({0,i/3.123,0});
        ball2->getParticle()->setRotation(rot);

    //  ball2->getParticle()->setAngularVelocity({1,1,0});
        ball2->getParticle()->applyForce({0,-10,0});

        world->addBall(ball2);
    }








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