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

file(GLOB INTERFACE "src/interface/*.hpp")

add_executable (rtype_client ${CLIENT_SRC} ${COMMON})

target_include_directories(rtype_client PUBLIC ${CONAN_INCLUDE_DIRS} /src/common /src/interface)
target_link_libraries(rtype_client PUBLIC ${CONAN_LIBS})

add_executable (rtype_server ${SERVER_SRC} ${COMMON})

target_include_directories(rtype_server PUBLIC ${CONAN_INCLUDE_DIRS} /src/common src/interface)
target_link_libraries(rtype_server PUBLIC ${CONAN_LIBS})