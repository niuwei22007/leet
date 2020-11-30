cmake_minimum_required(VERSION 3.17)
project(TrustDo)

set(CMAKE_CXX_STANDARD 17)

include_directories(
        trust.h
        #        ${PROJECT_SOURCE_DIR}/../../opt/android-ndk-r20b/sysroot/usr/include
)

file(GLOB SRC0 *.cpp)
file(GLOB SRC_s_d search/dfs/*.cpp)
file(GLOB SRC_s_b search/bfs/*.cpp)
file(GLOB SRC_s_bt search/backtrace/*.cpp)
file(GLOB SRC_dp dp/*.cpp)

add_executable(LeetCode
        ${SRC0}
        #        ${SRC_s_d}
#        ${SRC_s_b}
#        ${SRC_s_bt}
        ${SRC_dp}
        )