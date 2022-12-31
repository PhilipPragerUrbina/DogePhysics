//
// Created by Philip on 12/30/2022.
//

#pragma once

namespace Doge {
    //todo revise this and add it to particles and emmiters

    /*
     * PhysicsObject(group, spring) -> positionable(emmiter) -> physical/forceable(particle)
     * Colidable(seperate) -> positionable (something like this)
     * We migh also skip the whole positionable thing, we just need to make sure we can handle static(floor), abstract(group), position_based(emitter), ghost(particle), and physical(rigid body)
     * Make sure to check if damping is needed for forcible/physical objects or if that is just for particles
     * Also what about particles that collide, like for mass agregate or sparks.
     * What about querying collision detection, such as raycasts, or did porjectile actually hit! Mabeye a virtual onHit method for collidables.
     * What about static collidables, vs non-static, and how does the position(and rotation and scale) affect the collider, as well as things like emitters.
     * //fun
     */

    class PositionablePhysicsObject {

    };

} // Doge
