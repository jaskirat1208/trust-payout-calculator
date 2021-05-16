cmake_minimum_required(VERSION 3.10)

# set the project name
project(trust)

# add the executable
add_library(trust-calculator src/grat_calc.cpp)

target_include_directories(trust-calculator PUBLIC ${INTERNAL_INCLUDES}/trust)

target_include_directories(trust-calculator PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)