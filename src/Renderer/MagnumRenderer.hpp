//
// Created by Philip on 12/27/2022.
//

#pragma once
#include "Renderer.hpp"

#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/GL/Mesh.h>
#include <Magnum/GL/Renderer.h>
#include <Magnum/Math/Color.h>
#include <Magnum/Math/Matrix4.h>
#include <Magnum/MeshTools/Compile.h>
#include <Magnum/Platform/Sdl2Application.h>
#include <Magnum/Primitives/Cube.h>
#include <Magnum/Primitives/UVSphere.h>
#include <Magnum/Primitives/Cylinder.h>
#include <Magnum/Shaders/PhongGL.h>
#include <Magnum/Trade/MeshData.h>
#include <iostream>
#include <stack>
#include "Magnum/Math/Quaternion.h"
#include "Magnum/GL/Texture.h"
#include <MagnumPlugins/ObjImporter/ObjImporter.h>
#include "Magnum/Trade/TextureData.h"
#include <MagnumPlugins/AnyImageImporter/AnyImageImporter.h>
#include <Magnum/ImageView.h>
#include <Magnum/Trade/ImageData.h>
#include <Magnum/GL/TextureFormat.h>

//Use the magnum namespaces
using namespace Magnum;
using namespace Math::Literals;

/**
 * Magnum implementation of the renderer
 * Supposed to be used within a Magnum application, and passed into the draw event
 */
class MagnumRenderer : public Doge::Renderer{
private:

    std::vector<GL::Mesh> mesh_buffer; //The loaded meshes
    Shaders::PhongGL* shader; //The shader to render to

    Matrix4 projection ; //The camera projection matrix. Camera position is handled using the transformation matrix.

    Matrix4 current_matrix = Matrix4(); //The current transformation matrix
    std::stack<Matrix4> matrix_stack; //Stack of matrices

    /**
     * Update the transformation and normal matrix of shader
     * Call after any changes to the current matrix
     */
    void updateTransform(){
        shader->setTransformationMatrix(current_matrix).setNormalMatrix(current_matrix.normalMatrix());
    }

public:
    /**
     * Load a new renderer
     * Just renders to shader, does not handle background or buffer swap
     * @param render_to The shader to render to
     * @param window_dimensions Used to calculate aspect ratio
     */
    MagnumRenderer( Vector2 window_dimensions ){

        //load primitives
        mesh_buffer.emplace_back( MeshTools::compile(Primitives::cubeSolid())); //cube id 0
        mesh_buffer.emplace_back( MeshTools::compile(Primitives::cubeWireframe())); //cube wireframe id 1
        mesh_buffer.emplace_back( MeshTools::compile(Primitives::uvSphereSolid(10,10))); //sphere id 2
        mesh_buffer.emplace_back( MeshTools::compile(Primitives::cylinderSolid(10,10,0.5))); //Cylinder id 3
        //todo add more primitives such as capsule or cylinder

//https://doc.magnum.graphics/magnum/shaders.html
        Shaders::PhongGL::Configuration config;
        config.setFlags(Shaders::PhongGL::Flag::DiffuseTexture);
        shader = new Shaders::PhongGL(config); //todo delete




        //Set camera projection
        projection = Matrix4::perspectiveProjection(110.0_degf, window_dimensions.aspectRatio(), 0.1f, 1000.0f); //todo allow changing camera settings
        shader->setProjectionMatrix(projection);


    }

    /**
     * Load an obj mesh file
     * @param filename Obj file
     * @return Mesh index for use with drawMesh. 0 if failure(will render cube mesh).
     */
    unsigned int loadMesh(std::string filename) override {
        PluginManager::Manager<Trade::AbstractImporter> manager;
        Containers::Pointer<Trade::AbstractImporter> importer =
                manager.loadAndInstantiate("ObjImporter");

        if(importer->openFile(filename)){ //open the file
            mesh_buffer.push_back(MeshTools::compile(*importer->mesh(0))); //Add mesh
            return mesh_buffer.size()-1; //Return the mesh idx
        };
        return 0; //File could not be opened, return cube idx

    }
    //Load image
    GL::Texture2D texture;
    /**
     * Load and set current diffuse texture. Must be TGA format.
     */
    void loadTexture(std::string filename){
        //init importer
        PluginManager::Manager<Trade::AbstractImporter> manager;
        Containers::Pointer<Trade::AbstractImporter> importer =
                manager.loadAndInstantiate("TgaImporter");

        importer->openFile(filename); //read image

        Containers::Optional<Trade::ImageData2D> image = importer->image2D(0);   //get image


        texture.setWrapping(GL::SamplerWrapping::ClampToEdge)
                .setMagnificationFilter(GL::SamplerFilter::Linear)
                .setMinificationFilter(GL::SamplerFilter::Linear)
                .setStorage(1, GL::textureFormat(image->format()), image->size())
                .setSubImage(0, {}, *image);

        shader->bindDiffuseTexture(texture);//apply
    }


    void drawCube() override {
        shader->draw(mesh_buffer[0]);
    }

    void drawCylinder() override {
        shader->draw(mesh_buffer[3]);
    }

    void drawSphere() override {
        shader->draw(mesh_buffer[2]);
    }

    void drawCubeWireframe() override {
        shader->draw(mesh_buffer[1]);
    }

    void drawMesh(unsigned int id) override {
        if(id < mesh_buffer.size()){
            shader->draw(mesh_buffer[id]);
        }else{
            std::cerr << "Mesh not loaded: " << id << "\n";
        }
    }

    void inline setColor(unsigned char r, unsigned char g, unsigned char b) override {
        shader->setDiffuseColor(Color4((float)r/255.0f,(float)g/255.0f,(float)b/255.0f,1));
    }

    void inline pushMatrix() override {
        matrix_stack.push(current_matrix);//save old matrix
        //keep current matrix how it is(no need to update transform until further changes)
    }

    void translate(const Doge::Vector3&  translation) override {
        current_matrix = current_matrix * Matrix4::translation({(float )translation.x, (float )translation.y, (float )translation.z});
        updateTransform();
    }

    void scale(const Doge::Vector3&  scaling) override {
        current_matrix = current_matrix * Matrix4::scaling({(float )scaling.x, (float )scaling.y, (float )scaling.z});
        updateTransform();
    }

    void rotate(Doge::real angle_degrees, const Doge::Vector3&  direction) override {
        current_matrix = current_matrix * Matrix4::rotation(Deg{(float )angle_degrees}, {(float )direction.x, (float )direction.y, (float )direction.z});
        updateTransform();
    }

    void lookAt(const Doge::Vector3&  eye,const Doge::Vector3&  look_at, const Doge::Vector3&  up) override {
        current_matrix = current_matrix * Matrix4::lookAt({(float )eye.x, (float )eye.y, (float )eye.z},{(float )look_at.x, (float )look_at.y, (float )look_at.z}, {(float )up.x,(float )up.y,(float )up.z}).invertedRigid();
        updateTransform();
    }

    void rotate(const Doge::Quaternion &rotation) override{
        current_matrix = current_matrix * Matrix4(Math::Quaternion(Vector3{(float )rotation.i,(float )rotation.j,(float )rotation.k},(float )rotation.r).toMatrix());
    }

    void inline popMatrix() override {
        current_matrix = matrix_stack.top(); //revert to last matrix
        updateTransform();
        matrix_stack.pop(); //pop stack
    }

};
