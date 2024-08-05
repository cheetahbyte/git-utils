cmake_minimum_required(VERSION 3.28)
project(git_utils)

set(CMAKE_CXX_STANDARD 26)

add_executable(git_utils src/main.cpp
        src/gitutil.cpp
        src/gitutil.h
        src/commit.h
        src/commit.cpp
        src/common.h
        src/commitmessage.cpp
        src/commitmessage.h
        src/version.cpp
        src/version.h)
