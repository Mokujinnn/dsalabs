cmake_minimum_required(VERSION 3.5)

project(cource_work)

file(GLOB CPPS "src/*.cpp")
file(GLOB HPPS "include/*.cpp")

add_executable(${PROJECT_NAME} ${CPPS} ${HPPS})
target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include)