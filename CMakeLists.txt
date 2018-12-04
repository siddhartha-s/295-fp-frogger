cmake_minimum_required(VERSION 3.3)
project(frogger CXX)
include(.ipd/cmake/CMakeLists.txt)

add_program(model_test
        test/model_test.cpp
        src/model.cpp
        src/view.cpp
        src/controller.cpp)
target_link_libraries(model_test ge211 catch)

add_program(frogger
        src/frogger.cpp
        src/model.cpp
        src/view.cpp
        src/controller.cpp)
target_link_libraries(frogger ge211)
