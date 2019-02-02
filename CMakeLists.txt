cmake_minimum_required(VERSION 3.13)
project(ProjectCore)

set(CMAKE_CXX_STANDARD 14)

add_executable(ProjectCore main.cpp SymphonyNetwork.cpp SymphonyNetwork.hpp CommuncationsBuffer.cpp CommuncationsBuffer.hpp Communication.cpp Communication.hpp Controller.cpp Controller.hpp SensorHandler.cpp SensorHandler.hpp StateMachine.cpp StateMachine.hpp State.cpp State.hpp Instructor.cpp Instructor.hpp)