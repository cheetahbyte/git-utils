cmake_minimum_required(VERSION 3.28)
project(git_utils)

set(CMAKE_CXX_STANDARD 26)

set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

include(FetchContent)

FetchContent_Declare(
        fkYAML
        GIT_REPOSITORY https://github.com/fktn-k/fkYAML.git
        GIT_TAG v0.3.9
)
FetchContent_MakeAvailable(fkYAML)

FetchContent_Declare(
        args
        GIT_REPOSITORY https://github.com/Taywee/args
        GIT_TAG master
)

FetchContent_MakeAvailable(args)

add_executable(git_utils src/main.cpp
        src/gitutil.cpp
        src/gitutil.h
        src/commit.h
        src/commit.cpp
        src/common.h
        src/commitmessage.cpp
        src/commitmessage.h
        src/version.cpp
        src/version.h
        src/config.cpp
        src/config.h)
target_include_directories(${PROJECT_NAME} PRIVATE ${args_SOURCE_DIR})
target_link_libraries(git_utils PRIVATE fkYAML::fkYAML)
install(TARGETS git_utils DESTINATION bin)
include(CPack)