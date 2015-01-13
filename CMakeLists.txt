cmake_minimum_required(VERSION 2.8.8)

project(NeuRL)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_BUILD_TYPE Debug)

#Use C++11 Definitions
add_definitions(-std=c++11)

#Add Eigen dependency
find_package(Eigen REQUIRED)
include_directories(${EIGEN_INCLUDE_DIRS})

#Set RLGlue Libraries
set(RLGLUE_LIBS rlgluenetdev rlutils)

#Set up include and lib paths
include_directories(include /usr/local/include)
link_directories(/usr/local/lib)

#Compiler flag magic
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux" OR ${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -m64 -msse2")
elseif(WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif()

#Build the NeuRL Library
add_library(neurl src/neural_net.cpp src/neural_q.cpp)
target_link_libraries(neurl ${EIGEN_LIBRARIES})

#Build Mario agent
add_executable(mario_agent
  experiments/mario/mario_agent.cpp
  experiments/common/neurl_agent.cpp)
target_link_libraries(mario_agent rlagent neurl ${RLGLUE_LIBS})
