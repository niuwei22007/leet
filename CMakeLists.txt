cmake_minimum_required(VERSION 3.17)
project(TrustDo)

set(CMAKE_CXX_STANDARD 11)

include_directories(
        trust.h
#        ${PROJECT_SOURCE_DIR}/../../opt/android-ndk-r20b/sysroot/usr/include
)

file(GLOB SRC0 *.cpp)
file(GLOB SRC1 */*.cpp)
file(GLOB SRC2 */*/*.cpp)

add_executable(LeetCode
        ${SRC0}
        ${SRC1}
        ${SRC2}
        )