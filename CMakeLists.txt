cmake_minimum_required(VERSION 2.6)

file (GLOB gmi_sources *.cpp wlm/*.cpp) 
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

if (CMAKE_BUILD_TYPE MATCHES "Debug")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDEBUG")
endif (CMAKE_BUILD_TYPE MATCHES "Debug")

add_executable(
	gmi 
	${gmi_sources}
)

link_directories(
    /usr/local/lib/
    )

target_link_libraries( gmi 
    boost_system
    boost_thread
    glog
    )

