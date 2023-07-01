cmake_minimum_required(VERSION 3.20)
project(Cloth)

set(CMAKE_CXX_STANDARD 14)

add_executable(Cloth main.cpp gui/cloth_app.hpp gui/cloth_app.cpp engine/cloth.hpp engine/cloth.cpp
        engine/verlet/constraint.hpp engine/verlet/constraint.cpp engine/verlet/verlet_entity.hpp
        engine/verlet/verlet_entity.cpp engine/verlet/verlet_point.hpp engine/verlet/verlet_point.cpp)

include_directories(Cloth "C:/Program Files/SFML-2.5.1/include")

set(SFML_ROOT "C:/Program Files/SFML-2.5.1")
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Cloth ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

# Copy dlls to build
if(WIN32)
    file(GLOB BINARY_DEP_DLLS "${SFML_INCLUDE_DIR}/../bin/*.dll")
    file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
    file(GLOB MINGW_DEP_DLLS "C:/Program Files/mingw64/bin/*.dll")
    file(COPY ${MINGW_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif()
