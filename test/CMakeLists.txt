add_executable(nox-test
    catch_main.cpp
    test.cpp)
target_include_directories(nox-test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(nox-test PUBLIC nox)
add_test(NAME nox-test COMMAND nox-test)
