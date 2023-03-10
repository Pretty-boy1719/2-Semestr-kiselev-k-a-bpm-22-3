add_executable(rational.test rational.test.cpp)
target_link_libraries(rational.test rational doctest::doctest)
add_test(NAME rational.test COMMAND rational.test)