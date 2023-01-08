//
// Created by Philip on 1/7/2023.
//
//todo separate main.cpp from demo code
//That way you can save multiple demos, and load them as needed
//Create methods that simply add the demo objects and code into the scene graph called loadDemoFireworks(Graph)

/*
 *

    //todo artillery and the explosion


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



 */