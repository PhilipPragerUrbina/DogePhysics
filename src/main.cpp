
#include "Renderer/MagnumApplication.hpp"
#include "Renderer/Camera.hpp"

#include "DogeEngine/Scene/SceneGraph.hpp"
#include "DogeEngine/Scene/Objects/Empty.hpp"
#include "DogeEngine/Scene/Objects/Cube.hpp"
#include "Demo/XPBD/XPBD.cpp"
#include "Utils/Matrix3.hpp"

#include "DogePhysics/Collisions/Layers/CollisionLayer.hpp"
#include "Magnum/Math/Matrix3.h"


#include <float.h>
//check for nans(also does inexact, may not be actual problem like overflow or divide by 0)
//unsigned int fp_control_state = _controlfp(_EM_INEXACT, _MCW_EM);

int main() {





    //Create renderer
    MagnumApplication renderer("Renderer");



//Create Camera
    Doge::Camera cam({0, 40, -50}, {0, 0, 1});

//Create world
    Doge::SceneGraph scene(new Doge::Empty());


    //scene.addObject(new Doge::Cube());

    createSceneXPBD(&scene);


    renderer.setUpdateCallback([&cam, &scene](Doge::real delta_time) {

            scene.update(0.01); //update scene
          //  first = true;


        //update camera
        //cam.setDirection(particle.getPosition()-cam.getPosition());
    });

    bool first = true;
    renderer.setRenderCallback([&cam, &scene,&first](MagnumRenderer &renderer) {
        if(first){
            renderer.loadMesh("cat.obj"); //todo load once for whole scene rather than for each object
            renderer.loadTexture("cat.tga");
            first = false;
        }

        cam.push(renderer); //render camera

        scene.render(&renderer); //render scene

        cam.pop(renderer);
    });
    renderer.exec();

    //todo convert particles to force generator
    //todo optimize renderer, especially for particles
    //todo figure out colors


}