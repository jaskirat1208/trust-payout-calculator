cmake_minimum_required(VERSION 3.16.3)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)   
# set the project name
project(trust)

# add the executable
include_directories(include)
add_library(trust-calculator src/grat_calc.cpp)

# target_include_directories(trust-calculator PUBLIC ${INTERNAL_INCLUDES}/trust)

# target_include_directories(trust-calculator PRIVATE
#     $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#     $<INSTALL_INTERFACE:include>
# )


add_subdirectory(test)