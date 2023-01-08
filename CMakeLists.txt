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
add_executable(DogePhysics src/main.cpp src/Utils/Vector3.hpp src/Utils/real.hpp src/Utils/real.hpp src/Utils/Vector3.hpp src/Utils/Transform.hpp src/Renderer/MagnumApplication.hpp src/Renderer/MagnumApplication.hpp src/DogePhysics/PhysicsObjects/Systems/Emmiters/ProjectileGenerator.hpp src/Utils/Generators/CarGenerator.hpp src/DogePhysics/PhysicsObjects/Systems/Emmiters/FireworksEmitter.hpp src/Renderer/MagnumRenderer.hpp src/Renderer/Renderer.hpp src/Renderer/Camera.hpp src/DogePhysics/PhysicsObjects/Particles/Particle.hpp src/DogePhysics/PhysicsObjects/Systems/Emmiters/ExplosionGenerator.hpp src/DogePhysics/PhysicsObjects/Particles/LifetimeParticle.hpp src/Utils/Random.hpp src/DogeEngine/Scene/SceneGraph.hpp src/DogeEngine/IO/SceneParser.hpp src/DogeEngine/Scene/GameObject.hpp src/DogePhysics/PhysicsObjects/Systems/ParticleSystem.hpp src/DogePhysics/PhysicsObjects/PhysicsObject.hpp src/DogePhysics/PhysicsObjects/PositionablePhysicsObject.hpp src/DogePhysics/PhysicsObjects/Calculators/ForceCalculator.hpp src/DogePhysics/PhysicsObjects/Calculators/SimpleGravity.hpp src/DogePhysics/PhysicsObjects/Calculators/SimpleDrag.hpp src/DogePhysics/PhysicsObjects/Calculators/ComplexDrag.hpp src/DogePhysics/PhysicsObjects/Constraints/Groups/ForceGroup.hpp src/DogePhysics/PhysicsObjects/Constraints/Groups/UniversalGravitation.hpp src/Renderer/InputManager.hpp src/DogePhysics/Collisions/Colliders/SDFCollider.hpp src/Demo/Fireworks/FireworksDemo.cpp src/DogeEngine/Scene/Objects/Empty.hpp src/DogeEngine/Scene/Objects/Cube.hpp)
target_link_libraries(DogePhysics PRIVATE
        Corrade::Main
        Magnum::Application
        Magnum::GL
        Magnum::Magnum
        Magnum::MeshTools
        Magnum::Primitives
        Magnum::Shaders
        Magnum::Trade)


