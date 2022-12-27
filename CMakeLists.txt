cmake_minimum_required(VERSION 3.22)
project(DogePhysics)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH "external/modules/" ${CMAKE_MODULE_PATH})

add_subdirectory(external/corrade EXCLUDE_FROM_ALL)

# Add Magnum as a subproject, enable Sdl2Application
set(CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/SDL2-2.0.10 ${CMAKE_PREFIX_PATH})
set(MAGNUM_WITH_SDL2APPLICATION ON CACHE BOOL "" FORCE)
add_subdirectory(external/magnum EXCLUDE_FROM_ALL)

find_package(Magnum REQUIRED GL Sdl2Application)
set_directory_properties(PROPERTIES CORRADE_USE_PEDANTIC_FLAGS ON)
add_executable(DogePhysics src/main.cpp src/Utils/Vector3.hpp src/Utils/real.hpp src/Utils/real.hpp src/Utils/Vector3.hpp src/Utils/Transform.hpp)
target_link_libraries(MyApplication PRIVATE
        Magnum::Application
        Magnum::GL
        Magnum::Magnum)


