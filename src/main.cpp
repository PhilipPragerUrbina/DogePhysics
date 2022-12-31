
#include "Renderer/MagnumApplication.hpp"
#include "Renderer/Camera.hpp"

#include "DogePhysics/PhysicsObjects/particles/Particle.hpp"
#include "DogePhysics/PhysicsObjects/Systems/Emmiters/FireworksEmitter.hpp"
int main(int argc, char** argv){

    //todo scene graph
    //todo artillery and the explosion
    //todo forces(constant force means constant acceleration). Impulse forces over a period of time.
    //todo time-limited particle inheritance
    //todo return firework array of particles
    //todo firework spawns more particles
    //todo firework simulate colors, or provide info for the user calculation of colors
    //todo review generator structure to reduce the amount the user needs to do, should user step particles
    //todo should bullet be it's own special physics object that is applying its own forces to itself, or should it just be a particle, managed by gun object.
    //its all a question of how much is in the physics engine(inheriting from physics object), and how much is in the game engine or specific game(inheriting from game-object)
    //generator is simply a game engine agnostic physics scenario,bundled with the engine for convince, can also be done manually

MagnumApplication renderer ("Renderer");
Doge::Camera cam({0,2,-30},{0,0,1});
Doge::FireworksEmitter emitter(2,  50, 0.2,  {-5}, {5},
    5, 1, -0.7, 0.2);
emitter.launch({0,2,0});

renderer.setUpdateCallback([&cam,&emitter](Doge::real delta_time) {

   emitter.step(delta_time);
//std::cout << emitter.getParticleCount() << "\n";
    //cam.setDirection(particle.getPosition()-cam.getPosition());


});

renderer.setRenderCallback([&cam, &emitter](MagnumRenderer& renderer){
cam.push(renderer);
renderer.setColor(255,0,0);
emitter.renderParticles([&renderer](Doge::Particle* particle){
    renderer.pushMatrix();
    renderer.translate(particle->getPosition());
    renderer.scale(0.02);
    renderer.drawSphere();
    renderer.popMatrix();
});


    cam.pop(renderer);
});
    renderer.exec();

    //todo separate main.cpp from demo code
    //That way you can save multiple demos, and load them as needed
    //Create methods that simply add the demo objects and code into the scene graph called loadDemoFireworks(Graph)


    //todo scene graph
    //todo optimize renderer, especially for particles
    //todo fem, and signed distance field colliders for gears and other non convex shapes
    //https://developer.nvidia.com/physx-sdk
    //https://developer.nvidia.com/blog/open-source-simulation-expands-with-nvidia-physx-5-release/

}