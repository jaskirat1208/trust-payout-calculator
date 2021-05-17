find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

add_executable(trust-cal_test main.cpp grat_calc.cpp)

target_link_libraries(trust-cal_test trust-calculator ${GTEST_LIBRARIES} pthread)