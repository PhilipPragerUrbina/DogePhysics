
#include "Renderer/MagnumApplication.hpp"
#include "Renderer/Camera.hpp"

#include "DogeEngine/Scene/SceneGraph.hpp"
#include "DogeEngine/Scene/Objects/Empty.hpp"
#include "DogeEngine/Scene/Objects/Cube.hpp"

int main() {


    //Create renderer
    MagnumApplication renderer("Renderer");

//Create Camera
    Doge::Camera cam({0, 2, -30}, {0, 0, 1});

//Create world
    Doge::SceneGraph scene(new Doge::Empty());

    //todo set up demo scene
    scene.addObject(new Doge::Cube());

    renderer.setUpdateCallback([&cam, &scene](Doge::real delta_time) {
        scene.update(delta_time); //update scene
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