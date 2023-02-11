//
// Created by Philip on 12/27/2022.
//

#pragma once

#include "../Utils/Vector3.hpp"
#include "../Utils/Quaternion.hpp"

namespace Doge {

    /**
     * An interface for rendering objects
     * Used to stop rendering leakage into scene graph
     * Is an adapter to different rendering APIs
     * Camera projection is up to the implementation, but the camera position and rotation can be achieved by pushing matrices
     */
    class Renderer {
    public:

        /**
         * Load a mesh to draw later
         * @return The id of the loaded mesh for drawing
         */
        virtual unsigned int loadMesh(std::string filename)=0;//todo take either vertex data and/or a filename

        /**
         * Draw a primitive cube
         */
        virtual void drawCube() = 0;

        /**
       * Draw a cylinder tip facing y
       */
        virtual void drawCylinder() = 0;

        /**
         * Draw a primitive sphere
         */
        virtual void drawSphere() = 0;
        /**
         * Draw a wireframe box for debugging
         */
        virtual void drawCubeWireframe() = 0;
        /**
         * Draw a loaded mesh
         * @param id The id of the mesh you want to draw(Returned from loadMesh)
         */
        virtual void drawMesh(unsigned int id) = 0;

        /**
         * Set the color to render with
         * @param r red
         * @param g green
         * @param b blue
         */
        virtual inline void setColor(unsigned char r, unsigned char g, unsigned char b)= 0;

        /**
         * Add another matrix to the stack and make it active
         * Works like Opengl. Each new matrix pushed starts in the same state as the last active matrix. This results in the transformations of the objects drawn effectively being all transformations in the stack combined.
         * All transformations such as translate will be applied to the latest matrix pushed, in the order specified including draws in between.
         */
        virtual inline void pushMatrix() = 0;
        /**
         * Apply a translation to the active matrix
         * @param translation How much to move by
         */
        virtual void translate(const Doge::Vector3& translation) = 0;

        /**
         * Apply a scaling transformation to the active matrix
         * @param scaling Amount to scale by
         */
        virtual void scale(const Doge::Vector3&  scaling) = 0;

       /**
        * Apply a rotation to the active matrix
        * @param angle_degrees The angle to rotate by in degrees
        * @param direction A normalized vector direction to rotate in
        */
        virtual void rotate(real angle_degrees , const Doge::Vector3&  direction) = 0;

        //todo doc
        virtual void rotate(const Quaternion& rotation)= 0;

        /**
          * Rotate the active matrix to look at something
          * @param look_at The point to look at,
          * @param up The reference direction. What is up.
          * @param eye The point it is looking from
          */
        virtual void lookAt(const Doge::Vector3&  eye, const Doge::Vector3&  look_at, const Doge::Vector3&  up) = 0;

        /**
         * Remove the latest matrix from the stack and make it active
         * Effectively revert to last matrix.
         */
        virtual inline void popMatrix() = 0;

    };

} // Doge
