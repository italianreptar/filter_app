cmake_minimum_required(VERSION 3.21.3)
project(filter_app)
set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES src/filter_app.cpp)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_LIB_PREFIX "lib")
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
# set(Boost_DEBUG ON)
find_package(Boost 1.77 REQUIRED chrono)

if(Boost_FOUND)
    message("CZN: Boost Found!")
    message("Boost Include: ${Boost_INCLUDE_DIRS}")
    message("Boost Libraries: ${Boost_LIBRARY_DIRS}")
endif()

add_executable(filter_app ${SOURCE_FILES})
target_include_directories(
    filter_app
    PUBLIC
    includes
    ${Boost_INCLUDE_DIRS}
    Boost::boost
)
target_link_libraries(filter_app ${Boost_LIBRARIES})

add_custom_command(
    TARGET filter_app POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_SOURCE_DIR}/cfgs/filter_coeffs.json
    ${CMAKE_SOURCE_DIR}/build/filter_coeffs.json
)