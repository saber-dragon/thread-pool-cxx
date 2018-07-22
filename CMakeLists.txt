cmake_minimum_required(VERSION 3.10)
project(thread_pool)

set(CMAKE_CXX_STANDARD 11)

include(CheckIncludeFile)

file(GLOB thp_headers "*.h" "*hh" "*.hpp" "*.hxx")
set(thp_libraries "")

CHECK_INCLUDE_FILE("pthread.h" HAVE_PTHREAD)

if (HAVE_PTHREAD)
    add_definitions(-DHAVE_PTHREAD_H)
    list(APPEND thp_libraries "pthread")
else ()
    unset(HAVE_PTHREAD)
    message(FATAL_ERROR "pthread.h is not found")
endif ()

#set(target_name "thread_pool")
#add_library(${target_name} STATIC ${thp_headers} thread_pool.cc)
#target_link_libraries(${target_name} ${thp_libraries})
#target_include_directories(${target_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
#target_compile_definitions(${target_name} PUBLIC DEBUG)

#list(APPEND thp_libraries ${target_name})

set(target_name "${PROJECT_NAME}_test")
add_executable(${target_name} example.cpp)
target_link_libraries(${target_name} ${thp_libraries})