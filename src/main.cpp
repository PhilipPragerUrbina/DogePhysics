
#include "Renderer/MagnumApplication.hpp"
#include "Renderer/Camera.hpp"

#include "DogeEngine/Scene/SceneGraph.hpp"
#include "DogeEngine/Scene/Objects/Empty.hpp"
#include "DogeEngine/Scene/Objects/Cube.hpp"
#include "Demo/XPBD/XPBD.cpp"
#include "Utils/Matrix3.hpp"

#include "DogePhysics/Collisions/Layers/CollisionLayer.hpp"


#include <float.h>
//check for nans(also does inexact, may not be actual problem like overflow or divide by 0)
//unsigned int fp_control_state = _controlfp(_EM_INEXACT, _MCW_EM);

int main() {

    Doge::Quaternion a = {0.5,0,0,1};

    Doge::Quaternion b = a.inverse();
    Doge::Quaternion c = a;
    c*=b;
    std::cout << c.i << " " << c.j << " " << c.k << " " << c.r << "\n";

    Quaternion a2 = Quaternion{{0.5f,0.0f,0.0f},1.0f};
    a2 =  a2 * a2.inverted();
    std::cout << a2.data()[0] << " " << a2.data()[1] << " " << a2.data()[2] << " " << a2.data()[3] << "\n";


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
            scene.update(0.01); //update scene
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