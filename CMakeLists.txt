cmake_minimum_required(VERSION 2.8.8)

project(NeuRL)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

#Add Eigen dependency
find_package(Eigen REQUIRED)
include_directories(${EIGEN_INCLUDE_DIRS})

#Set up include and lib paths
include_directories(include)

#Compiler flag magic
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux" OR ${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
			set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -m64 -msse2")
elseif(WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif()

#Build the NeuRL Library
add_library(neurl src/neural_net.cpp src/neural_q.cpp)
target_link_libraries(neurl ${EIGEN_LIBRARIES})

#Create the example Mario agent executable
#add_executbale(mario_agent experiments/mario/marioAgent.cpp)
#target_link_libraries(mario_agent neurl)
