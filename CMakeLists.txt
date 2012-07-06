
file (GLOB gmi_sources *.cpp) 
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable(
	gmi 
	${gmi_sources}
)

target_link_libraries( gmi boost_system boost_thread )

