
#include "Renderer/MagnumApplication.hpp"
#include "Renderer/Camera.hpp"

#include "DogeEngine/Scene/SceneGraph.hpp"
#include "DogeEngine/Scene/Objects/Empty.hpp"
#include "DogeEngine/Scene/Objects/Cube.hpp"
#include "Demo/XPBD/XPBD.cpp"
#include "Utils/Matrix3.hpp"




#include <float.h>
unsigned int fp_control_state = _controlfp(_EM_INEXACT, _MCW_EM);

int main() {


    //Create renderer
    MagnumApplication renderer("Renderer");

//Create Camera
    Doge::Camera cam({0, 2, -20}, {0, 0, 1});

//Create world
    Doge::SceneGraph scene(new Doge::Empty());


    //scene.addObject(new Doge::Cube());

    createSceneXPBD(&scene);

    bool first = false;
    renderer.setUpdateCallback([&cam, &scene, &first](Doge::real delta_time) {
        if(!first){
            scene.update(delta_time); //update scene
          //  first = true;
        }

        //update camera
        //cam.setDirection(particle.getPosition()-cam.getPosition());
    });


    renderer.setRenderCallback([&cam, &scene](MagnumRenderer &renderer) {
        cam.push(renderer); //render camera

        scene.render(&renderer); //render scene

        cam.pop(renderer);
    });
    renderer.exec();

    //todo convert particles to force generator
    //todo optimize renderer, especially for particles
    //todo figure out colors


}