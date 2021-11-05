cmake_minimum_required(VERSION 3.10)

project(rtype)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

include(build/conanbuildinfo.cmake)
conan_basic_setup(KEEP_RPATHS)

include_directories(${CONAN_INCLUDE_DIRS})
link_directories(${CONAN_LIBRARIES_DIRS})

file(GLOB CLIENT_SRC "src/client/*.cpp" "src/client/*.hpp" "src/client/Parallax/*.cpp" "src/client/Parallax/*.hpp" "src/client/Entity/*.cpp" "src/client/Entity/*.hpp" "src/client/Window/*.cpp" "src/client/Window/*.hpp")

file(GLOB SERVER_SRC "src/server/*.cpp" "src/server/*.hpp")

file(GLOB COMMON "src/common/*.cpp" "src/common/*.hpp")

file(GLOB INTERFACE "src/interface/*.hpp")

add_executable (rtype_client ${CLIENT_SRC} ${COMMON})

target_include_directories(rtype_client PUBLIC ${CONAN_INCLUDE_DIRS} /src/common /src/interface)
target_link_libraries(rtype_client PUBLIC ${CONAN_LIBS})
# target_link_libraries(rtype_client sfml-graphics sfml-window sfml-system sfml-audio sfml-network)

add_executable (rtype_server ${SERVER_SRC} ${COMMON})

include_directories("src/interface")
include_directories("src/common")
include_directories("src/client")
include_directories("src/server")
include_directories("src/client/Parallax")
include_directories("src/client/Entity")
include_directories("src/client/Window")

target_include_directories(rtype_server PUBLIC ${CONAN_INCLUDE_DIRS} /src/common src/interface)
target_link_libraries(rtype_server PUBLIC ${CONAN_LIBS})

if(CMAKE_COMPILER_IS_GNUCXX)
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
	list(APPEND SERVER_COMPILE_OPTIONS "/std:c++14 -D_WIN32_WINNT=0x0A00")
	list(APPEND CLIENT_COMPILE_OPTIONS "/std:c++14")
	foreach(ITEM ${SERVER_COMPILE_OPTIONS})
		set_source_files_properties(${SERVER_SRC} PROPERTIES COMPILE_FLAGS ${ITEM})
	endforeach(ITEM in SERVER_COMPILE_OPTIONS)
	foreach(ITEM ${CLIENT_COMPILE_OPTIONS})
		set_source_files_properties(${CLIENT_SRC} PROPERTIES COMPILE_FLAGS ${ITEM})
	endforeach(ITEM in CLIENT_COMPILE_OPTIONS)
endif(MSVC)