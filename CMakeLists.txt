cmake_minimum_required(VERSION 2.8.4)

project(DooR)

# try enalble c++11
# g++ need flags to enable c++11
include(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-std=c++11" HAS_CPP11)
if (HAS_CPP11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb -std=c++11 -lrt")
endif()

# search file and insert value to first argument, APISrcs
file(GLOB APISrcs "./src/*.cpp")

# add includes for all
include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src")

# install package
find_package(door_shared_memory REQUIRED)
find_package(door_bridge REQUIRED)

# select executable file
add_executable(DooR ${APISrcs})
target_link_libraries(DooR door_shared_memory)
target_link_libraries(DooR door_bridge)
target_link_libraries(DooR door_api)
target_link_libraries(DooR door_unix_domain_socket_client)

