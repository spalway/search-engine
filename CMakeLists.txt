cmake_minimum_required(VERSION 3.15)
project(FinalProjExamples)

# filesystem.h require C++17
set(CMAKE_CXX_STANDARD 17)

file(COPY sample_data/ DESTINATION sample_data/)

# show compiler output and enable warnings
set(CMAKE_VERBOSE_MAKEFILE ON)
add_compile_options(-Wall -Wextra -pedantic)

add_executable(rapidJSONExample rapidJSONExample.cpp)
add_executable(supersearch main.cpp porter2_stemmer.cpp DocumentParser.cpp Query.cpp UserInterface.cpp Index.cpp)

add_executable(testAvlTree testAvlTree.cpp AvlTree.h )
add_test(NAME TestAVLTree COMMAND testAvlTree)

add_executable(testquery testQuery.cpp porter2_stemmer.cpp DocumentParser.cpp Query.cpp UserInterface.cpp Index.cpp)
add_test(NAME Testquery COMMAND testquery)

add_executable(testIndex testIndex.cpp Index.h )
add_test(NAME TestIndex COMMAND testIndex)

# this makes sure we also link rapidjson
target_include_directories(rapidJSONExample PRIVATE rapidjson/)

set(CMAKE_VERBOSE_MAKEFILE OFF)
