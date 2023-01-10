cmake_minimum_required(VERSION 3.22)
project(DogePhysics)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/external/modules/" ${CMAKE_MODULE_PATH})

add_subdirectory(external/corrade EXCLUDE_FROM_ALL)

# Add Magnum as a subproject, enable Sdl2Application
set(CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/external/SDL2-2.24.2" ${CMAKE_PREFIX_PATH})
set(MAGNUM_WITH_SDL2APPLICATION ON CACHE BOOL "" FORCE)
add_subdirectory(external/magnum EXCLUDE_FROM_ALL)

find_package(Magnum REQUIRED
        GL
        MeshTools
        Primitives
        Shaders
        Trade
        Sdl2Application)
set_directory_properties(PROPERTIES CORRADE_USE_PEDANTIC_FLAGS ON)
add_executable(DogePhysics src/main.cpp src/Utils/Vector3.hpp src/Utils/real.hpp src/Utils/real.hpp src/Utils/Vector3.hpp src/Utils/Matrix4.hpp src/Renderer/MagnumApplication.hpp src/Renderer/MagnumApplication.hpp src/DogePhysics/PhysicsObjects/Systems/Emmiters/ProjectileGenerator.hpp src/Utils/Generators/CarGenerator.hpp src/DogePhysics/PhysicsObjects/Systems/Emmiters/FireworksEmitter.hpp src/Renderer/MagnumRenderer.hpp src/Renderer/Renderer.hpp src/Renderer/Camera.hpp src/DogePhysics/PhysicsObjects/Particles/Particle.hpp src/DogePhysics/PhysicsObjects/Systems/Emmiters/ExplosionGenerator.hpp src/DogePhysics/PhysicsObjects/Particles/LifetimeParticle.hpp src/Utils/Random.hpp src/DogeEngine/Scene/SceneGraph.hpp src/DogeEngine/IO/SceneParser.hpp src/DogeEngine/Scene/GameObject.hpp src/DogePhysics/PhysicsObjects/Systems/ParticleSystem.hpp src/DogePhysics/PhysicsObjects/PhysicsObject.hpp src/DogePhysics/PhysicsObjects/PositionablePhysicsObject.hpp src/DogePhysics/ForceCalculators/ForceCalculator.hpp src/DogePhysics/ForceCalculators/SimpleGravity.hpp src/DogePhysics/ForceCalculators/SimpleDrag.hpp src/DogePhysics/ForceCalculators/ComplexDrag.hpp src/DogePhysics/PhysicsObjects/Constraints/Groups/ForceGroup.hpp src/DogePhysics/PhysicsObjects/Constraints/Groups/UniversalGravitation.hpp src/Renderer/InputManager.hpp src/DogePhysics/Collisions/Colliders/SDFCollider.hpp src/Demo/Fireworks/FireworksDemo.cpp src/DogeEngine/Scene/Objects/Empty.hpp src/DogeEngine/Scene/Objects/Cube.hpp src/DogePhysics/Collisions/Colliders/BoxCollider.hpp src/DogePhysics/Collisions/Colliders/CompoundCollider.hpp src/DogePhysics/Collisions/Colliders/Collider.hpp src/DogePhysics/Collisions/Layers/CollisionLayer.hpp src/DogePhysics/Collisions/Layers/CompoundLayer.hpp src/DogePhysics/Collisions/Layers/Octree/OctreeLayer.hpp src/DogePhysics/Collisions/Layers/Octree/StaticOctreeLayer.hpp src/DogePhysics/Group.hpp src/DogePhysics/Constraints/Constraint.hpp src/DogePhysics/Constraints/Fixed/Spring.hpp src/DogePhysics/ForceCalculators/Groups/UniversalGravitation.hpp src/DogePhysics/Constraints/Groups/CollisionSolver.hpp src/DogePhysics/Constraints/Groups/SimpleFloor.hpp src/DogePhysics/Objects/Transformable.hpp src/DogePhysics/Objects/Updateable.hpp src/DogePhysics/Objects/Collideable.hpp src/DogePhysics/Objects/Static.hpp src/DogePhysics/Objects/Physical.hpp src/DogePhysics/Constraints/ConstraintManager.hpp src/DogePhysics/Objects/XPBD/Constrainable.hpp src/DogePhysics/Objects/XPBD/RigidBody.hpp src/DogePhysics/Objects/XPBD/ParticleSystems/Emmiters/Cloth.hpp src/DogePhysics/Objects/XPBD/ParticleSystems/Emmiters/Sparks.hpp src/DogePhysics/Objects/XPBD/ParticleSystems/Emmiters/ProjectileLauncher.hpp src/DogePhysics/Objects/XPBD/ParticleSystems/Particles/RigidParticle.hpp src/DogePhysics/Objects/XPBD/ParticleSystems/Particles/Projectile.hpp src/DogePhysics/Objects/XPBD/ParticleSystems/Particles/ConstrainableParticle.hpp src/Utils/Matrix3.hpp src/DogePhysics/Objects/Positionable.hpp src/Utils/Quaternion.hpp)
target_link_libraries(DogePhysics PRIVATE
        Corrade::Main
        Magnum::Application
        Magnum::GL
        Magnum::Magnum
        Magnum::MeshTools
        Magnum::Primitives
        Magnum::Shaders
        Magnum::Trade)


