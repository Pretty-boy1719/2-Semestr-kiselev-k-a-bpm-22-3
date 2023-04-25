add_executable(rational.test rational.test.cpp "rational.test.cpp")
target_link_libraries(rational.test rational doctest::doctest)
add_test(NAME rational.test COMMAND rational.test)

add_executable(arrayd.test arrayd.test.cpp "arrayd.test.cpp")
target_link_libraries(arrayd.test arrayd doctest::doctest)
add_test(NAME arrayd.test COMMAND arrayd.test)

add_executable(matrixs.test matrixs.test.cpp "matrixs.test.cpp")
target_link_libraries(matrixs.test matrixs doctest::doctest)
add_test(NAME matrixs.test COMMAND matrixs.test)

add_executable(arrayt.test arrayt.test.cpp "arrayt.test.cpp")
target_link_libraries(arrayt.test arrayt doctest::doctest)
add_test(NAME arrayt.test COMMAND arrayt.test)



