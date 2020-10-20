cmake_minimum_required(VERSION 3.17)
project(TrustDo)

set(CMAKE_CXX_STANDARD 11)

#include_directories(
#        ${PROJECT_SOURCE_DIR}/../../opt/android-ndk-r20b/sysroot/usr/include
#)

add_executable(TrustDo main.cpp trust.h prefix_tree/trie_208.cpp prefix_tree/word_replace_648.cpp prefix_tree/magic_dict_676.cpp contains_npu.cpp)