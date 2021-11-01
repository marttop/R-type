cmake_minimum_required( VERSION 3.10 )

project(rtype)

set(CMAKE_AUTOMOC ON)

include(build/conanbuildinfo.cmake)
conan_basic_setup(KEEP_RPATHS)

include_directories(${CONAN_INCLUDE_DIRS})

link_directories(${CONAN_LIBRARIES_DIRS})


file(GLOB CLIENT_SRC "src/client/*.cpp" "src/client/*.hpp")

file(GLOB SERVER_SRC "src/server/*.cpp" "src/server/*.hpp")

file(GLOB COMMON "src/common/*.cpp" "src/common/*.hpp")


add_executable (babel_client ${CLIENT_SRC} ${COMMON})

target_include_directories(babel_client PUBLIC ${CONAN_INCLUDE_DIRS} /src/common)
target_link_libraries(babel_client PUBLIC ${CONAN_LIBS})

add_executable (babel_server ${SERVER_SRC} ${COMMON})

target_include_directories(babel_server PUBLIC ${CONAN_INCLUDE_DIRS} /src/common)
target_link_libraries(babel_server PUBLIC ${CONAN_LIBS})