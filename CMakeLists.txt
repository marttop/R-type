cmake_minimum_required(VERSION 3.10)

project(rtype)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
SET(CMAKE_CXX_FLAGS  "-g3")

include(build/conanbuildinfo.cmake)
conan_basic_setup(KEEP_RPATHS)


include_directories(${CONAN_INCLUDE_DIRS})
link_directories(${CONAN_LIBRARIES_DIRS})

file(GLOB CLIENT_SRC "src/client/*.cpp" "src/client/*.hpp" "src/client/parallax/*.cpp" "src/client/parallax/*.hpp" "src/client/entity/*.cpp" "src/client/entity/*.hpp" "src/client/window/*.cpp" "src/client/window/*.hpp" "src/client/menu/*.cpp" "src/client/menu/*.hpp" "src/client/game/*.cpp" "src/client/game/*.hpp")

file(GLOB SERVER_SRC "src/server/*.cpp" "src/server/*.hpp" "src/server/engine/*.cpp" "src/server/engine/*.hpp")

file(GLOB COMMON "src/common/*.cpp" "src/common/*.hpp")

file(GLOB INTERFACE "src/interface/*.hpp")

add_executable (rtype_client ${CLIENT_SRC} ${COMMON})


target_include_directories(rtype_client PUBLIC ${CONAN_INCLUDE_DIRS} /src/common /src/interface)
target_link_libraries(rtype_client PUBLIC ${CONAN_LIBS})


include_directories("src/interface")
include_directories("src/common")
include_directories("src/client")
include_directories("src/server")
include_directories("src/client/parallax")
include_directories("src/client/entity")
include_directories("src/client/window")
include_directories("src/client/menu")
include_directories("src/client/game")
include_directories("src/server/engine")


if(CMAKE_COMPILER_IS_GNUCXX)
	add_executable (rtype_server ${SERVER_SRC} ${COMMON})
	target_include_directories(rtype_server PUBLIC ${CONAN_INCLUDE_DIRS} /src/common src/interface)
	target_link_libraries(rtype_server PUBLIC ${CONAN_LIBS})
	list(APPEND CLIENT_COMPILE_OPTIONS "-std=c++14 -W -Wall -Wextra")
	list(APPEND SERVER_COMPILE_OPTIONS "-std=c++14 -W -Wall -Wextra")
	foreach(ITEM ${SERVER_COMPILE_OPTIONS})
		set_source_files_properties(${SRC_SERVER} PROPERTIES COMPILE_FLAGS ${ITEM})
	endforeach(ITEM in SERVER_COMPILE_OPTIONS)
	foreach(ITEM ${CLIENT_COMPILE_OPTIONS})
		set_source_files_properties(${SRC_CLIENT} PROPERTIES COMPILE_FLAGS ${ITEM})
	endforeach(ITEM in CLIENT_COMPILE_OPTIONS)
endif(CMAKE_COMPILER_IS_GNUCXX)

if(MSVC)
	add_definitions(-DWIN32_LEAN_AND_MEAN)
	list(APPEND CLIENT_COMPILE_OPTIONS "/std:c++14 /wd4530")
	foreach(ITEM ${CLIENT_COMPILE_OPTIONS})
		set_source_files_properties(${CLIENT_SRC} PROPERTIES COMPILE_FLAGS ${ITEM})
	endforeach(ITEM in CLIENT_COMPILE_OPTIONS)
endif(MSVC)