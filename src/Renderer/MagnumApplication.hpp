//
// Created by Philip on 12/27/2022.
//

#pragma once

#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/GL/Mesh.h>
#include <Magnum/GL/Renderer.h>
#include <Magnum/Math/Color.h>
#include <Magnum/Math/Matrix4.h>
#include <Magnum/MeshTools/Compile.h>
#include <Magnum/Platform/Sdl2Application.h>
#include <Magnum/Primitives/Cube.h>
#include <Magnum/Shaders/PhongGL.h>
#include <Magnum/Trade/MeshData.h>
#include <functional>
#include "MagnumRenderer.hpp"
#include <chrono>
//Use the magnum namespaces
using namespace Magnum;
using namespace Math::Literals;

/**
 * The main graphics application using Magnum
 * Handles events and contains the renderer
 */
class MagnumApplication : public Platform::Application {
public:
    /**
     * Instantiate the application
     * @param window_name The name of the window
     */
    explicit MagnumApplication(const std::string& window_name) : Platform::Application{Arguments(argc, argv), Configuration{}.setTitle(window_name)} ,renderer(&shader, Vector2{windowSize()}){ //Set up the application and the renderer
        //enable render features
        GL::Renderer::enable(GL::Renderer::Feature::DepthTest);
        GL::Renderer::enable(GL::Renderer::Feature::FaceCulling);

        shader.setLightPositions({{10.4f, 1.0f, 0.75f, 0.0f}}); //Set the light positions
    }

    /**
     * Set the method or lambda to be called every time the render loop runs. This is where you draw your stuff.
     * Already has cleared buffer, and will swap buffer as well, you only need to call the draw methods on the renderer
     */
    void setRenderCallback(const std::function<void(MagnumRenderer&)> &new_render_callback) {
        render_callback = new_render_callback;
    }

    /**
     * Set the method to call to update the state
     * Runs every tick
     * Also supplies delta time in seconds
     */
    void setUpdateCallback(const std::function<void(double )> &new_update_callback) {
        update_callback = new_update_callback;
    }

    /**
     * Set the method to call before exit
     * Do your cleanup here
     */
    void setExitCallback(const std::function<void()> &new_exit_callback) {
        exit_callback = new_exit_callback;
    }
private:
    int argc; //arguments
    char** argv = new char*[0];

    Shaders::PhongGL shader; //The default shader, used in the renderer

    //callbacks
    std::function<void(MagnumRenderer&)> render_callback;
    std::function<void(double)> update_callback;
    std::function<void()> exit_callback;

    //actual renderer
    MagnumRenderer renderer;

    //Used to calculate delta time
    std::chrono::time_point< std::chrono::high_resolution_clock> last_time =  std::chrono::high_resolution_clock::now();


    void tickEvent() override{
        double delta_time = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - last_time).count(); //get delta time in seconds
        last_time = std::chrono::high_resolution_clock::now() ;
        if(update_callback){
            update_callback(delta_time);
        }
    }

    void exitEvent(ExitEvent &event) override{
        if(exit_callback){
            exit_callback();
        }
        event.setAccepted(true);
    }

    void drawEvent() override{
        GL::defaultFramebuffer.clear(GL::FramebufferClear::Color | GL::FramebufferClear::Depth); //start frame

        if(render_callback){
            render_callback(renderer);
        }

        swapBuffers(); //end frame
        redraw(); //update as many times as possible
    }


};
