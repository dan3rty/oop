cmake_minimum_required(VERSION 3.26)
project(ShapesApp)

enable_testing()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 20)
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin")
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG        2.6.x
)

FetchContent_MakeAvailable(SFML)

add_subdirectory(src)

add_executable(ShapesApp main.cpp)

target_link_libraries(ShapesApp PRIVATE canvas sfml-graphics sfml-window sfml-system)
if (WIN32)
    add_custom_command(
            TARGET ShapesApp
            COMMENT "Copy OpenAL DLL"
            PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:ShapesApp>
            VERBATIM)
endif()

install(TARGETS ShapesApp)

add_subdirectory(test)

add_dependencies(ShapesApp run_tests)