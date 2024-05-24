include(AddCatch2)

FILE(GLOB_RECURSE SRC "*.cpp")
add_executable(tests ${SRC}
        ../src/ICanvas.h
        ../src/CCanvas.cpp
        ../src/CCanvas.h)
target_link_libraries(tests PRIVATE canvas Catch2::Catch2WithMain sfml-graphics sfml-window sfml-system)

include(CTest)
include(Catch)
catch_discover_tests(tests)

add_custom_target(run_tests
        COMMAND tests
        DEPENDS tests
)